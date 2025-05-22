# Onderzoek Database



## Inleiding

In dit document licht ik mijn onderzoek naar een geschikte database toe. De [opdracht](../process/PvA.markdown#4-doelstelling-opdracht-en-op-te-leveren-resultaten-voor-het-bedrijf) staat beschreven in het PvA. Uiteindelijk wordt dit de grondslag van het database-gedeelte in mijn SDD. Ik beantwoord de deelvragen en de hoofdvragen en ik doe praktische tests om de uitkomst te valideren. 

## Onderzoeksvraag

Wat is de beste oplossing voor het opslaan en ophalen van sensordata?

Om deze vraag te beantwoorden moeten de volgende deelvragen beantwoord worden:

1. Wat voor data moet er worden opgeslagen?
2. Hoeveel data moet er worden opgeslagen?
3. Welke soorten opslag zijn gemaakt voor het soort data en de hoeveelheid ervan?

## Gebruikte methoden

De onderzoeksmethoden die ik gebruik komen uit de ICT Research Methods.

Voor deelvraag 1 gebruik ik een kleine interview en literatuuronderzoek.

Voor deelvraag 2 gebruik ik literatuuronderzoek.

Voor deelvraag 3 gebruik ik available product analysis.

Voor de hoofdvraag gebruik ik de antwoorden op de deelvragen en doe ik een test van de database met mock-data.



## Deelvraag 1: Wat voor data moet er worden opgeslagen?

Deze vraag vereist zowel op het gebied van eisen een antwoord, als op het praktische vlak. Om de eis van dit onderdeel vast te stellen moet ik weten of mijn systeem pre-processing op de data moet uitvoeren. 

Stel dat er een heel simpel systeem is, dat bestaat uit een watertoevoer met 1 klep met 1 flowsensor. Wanneer de klep aangestuurd wordt om open te gaan, dan duurt het heel even voordat het water gaat stromen. Deze tussentijd is relevant voor de stakeholder. Moet ik dan de tussentijd opslaan en om welke klep en sensor het gaat (pre-processing), of gewoon timestamped data?

De stakeholder heeft gekozen voor de tweede methode. De verwerking en interpretatie van de data wordt op een latere plek in de sequentie gedaan. Op deze manier gaat er geen data verloren die wellicht alsnog handig was. 

Praktisch gezien: Welke sensoren zitten er op de installatie? Hiervoor heb ik de IO-lijst die bij het PLC-programmeren is gebruikt. Op deze lijst staat van alle sensoren en actuatoren wat voor merk, welk model en wat voor datatype(hoeveelheid bytes) ze hebben. 

Volgens de IO-lijst zijn de meeste sensoren en actuatoren aangestuurd of uitgelezen met een binaire waarde. Dit zijn de kleppen en hun feedbacksensoren, levelsensoren voor vloeistof in de tanks en de pompen. In totaal zijn dit 93 bits. 

Daarnaast beschikken de IO-link sensoren over preciezere data: 2 of 4 bytes. Dit zijn 20 sensoren in de installatie. Deze sensoren meten temperatuur, flowrate of druk. Hoeveel opslag dit uiteindelijk gebruikt hangt af van de indeling van de DB.



## Deelvraag 2: Hoeveel data moet er worden opgeslagen?

Wanneer ik een IO-link master van de Soda Factory benader via zijn IoT-Port, dan geeft deze een handige webpagina terug met wat globale waarden: Wat voor sensor zit er op welke poort en wat is de cyclustijd van die port. Dit blijkt gemiddeld zo'n 5ms te zijn. In het ideale geval kan ik dus ongeveer elke 5ms data ophalen van de IO-Link masters. 

Stel dat ik alle data wil opslaan, dan moet ik 200x per seconde alle sensorwaarden van de hele installatie wegschrijven. Dat betekent dat 113*200, oftewel 22600 writes per *seconde* in het ergste geval. Wanneer ik de sensorwaarden echter opspaar en groepeer dan kan dit aantal heel sterk verminderd worden. Daarnaast is het de vraag *hoeveel* van deze data daadwerkelijk nodig is. 



## Deelvraag 3: Welke soorten opslag zijn gemaakt voor het soort data en de hoeveelheid ervan?

Aangezien de database gebruikt wordt voor sensorwaarden in de tijd is het handig om een "time series database" te gebruiken (Foote, 2022). De website [db-engines.com](https://db-engines.com) heeft een uitgebreide lijst waarin verschillende databases staan. Deze lijst is vooral op populariteit gesorteerd (*DB-Engines Ranking*, z.d.), wat voor mijn doeleind niet perse relevant is, maar wel handig. Hoe populairder een soort database is, hoe meer online ondersteuning er ook voor is. De populariteit zal dus als tie-breaker functioneren. 

Vanuit mijn opleiding heb ik het meeste in C/C++ geprogrammeerd en ben ik het bekendst met de ontwikkeltools, testtools en ontwikkelomgeving. Daarom zijn een C of C++ API en Linux-ondersteuning vereist voor de database. Zo kan de hele codebase van het project C++ blijven en dat maakt het builden en testen makkelijker. Verder moet de database een open source licentie hebben zodat ik hem mag gebruiken. 

De volgende "time series databases" zijn beschikbaar en zijn de populairste:

| Naam            | Ondersteunt C/C++ API | Ondersteunt Linux | Open source licentie |
| --------------- | --------------------- | ----------------- | -------------------- |
| InfluxDB        | Nee                   | Ja                | Ja                   |
| Prometheus      | Nee                   | Ja                | Ja                   |
| Kdb             | Ja                    | Ja                | Nee                  |
| Graphite        | Nee                   | Ja                | Ja                   |
| **TimescaleDB** | Ja                    | Ja                | Ja                   |
| QuestDB         | Nee                   | Ja                | Ja                   |

TimescaleDB komt hieruit als enige die aan alle eisen voldoet. Dit is een extentie op PostgreSQL en biedt dezelfde C interface als PostgreSQL waardoor het goed bruikbaar is voor mijn project. TimescaleDB biedt een aantal optimalisaties voor het opslaan en ophalen van timestamped data waardoor het zowel goed is om data weg te schrijven als om data op te halen voor analyse of voor de gebruikersinterface. 

Data met de meest recente timestamp moet altijd vooraan de database komen dus de db-engine hoeft niet te zoeken naar de juiste plek om te schrijven (*Timescale Documentation | About Writing Data*, z.d.). De database slaat daarnaast de data op in groepen van een bepaalde tijdsduur, waardoor er bij een query heel veel data genegeerd kan worden dat buiten de gespecificeerde groep valt. Deze optimalisatie werkt alleen wanneer er een query op basis van een timestamp of een range wordt gedaan, wanneer er op bijvoorbeeld een specifieke sensorwaarde wordt gezocht is er geen optimalisatie. 

## Test TimescaleDB

In deze test installeer ik TimescaleDB op mijn computer en schrijf ik zoveel mogelijk records als mogelijk. In de eerste test maak ik per datapunt een INSERT-statement. Dit is het *worst-case scenario* voor de database en het is meer de bedoeling om te zien dat de database werkt en hoeveel writes hij aan kan. Hiervoor gebruik ik de volgende Python-code:

```python
# Python test script to test the TimescaleDB database connection and basic operations at 22000 write operations per second and quits when ctrl+c is pressed.
# This script assumes that you have a PostgreSQL/TimescaleDB database running and a table named 'sodafactory' created with the following schema:
# CREATE TABLE IF NOT EXISTS sodafactory (
#     time    TIMESTAMPTZ  NOT NULL,
#     sensorid INTEGER NOT NULL,
#     data    DOUBLE PRECISION NOT NULL
# );

import psycopg2
import time
import sys
import signal
import os



# Connect to the PostgreSQL database
conn = psycopg2.connect(
    host="localhost",
    database="postgres",
    user="postgres",
    password="123"
)
writes = 0

#CTRL_C handler that closes DB connection peacefully and reports the amount of writes.
def quit(signal_number,frame):
    conn.close()
    print("Writes: " + str(writes))


signal.signal(signal.SIGINT, quit)



while True:
    # Create a cursor object
    cur = conn.cursor()
    # Execute a query to insert data into the table using NOW() for the time column
    cur.execute("INSERT INTO sodafactory (time, sensorid, data) VALUES (NOW(), %s, %s)", (1, 1))

    # Commit the transaction
    conn.commit()
    writes += 1
    # Close the cursor
    cur.close()
    # Sleep for a short time to control the rate of insertion
    time.sleep(0.000078)  # 1/22000, 22000 writes per second
    
```

Met deze implementatie haalde ik in 20 seconden 6075 writes, dus slechts 303 writes per seconde. Dat is veel minder dan de beoogde 22000 writes per seconde, maar met extra optimalisatie kan ik denk ik dichter in de buurt komen. 

```python
while True:
    # Create a cursor object
    cur = conn.cursor()
    queryStr = "INSERT INTO sodafactory (time, sensorid, data) "
    for i in range(0,49):
        queryStr += " VALUES (NOW(), 1, 13.2),"

    queryStr += "VALUES (NOW(), 1, 13.2);"
    # Execute a query to insert data into the table using NOW() for the time column
    cur.execute(queryStr)

    # Commit the transaction
    conn.commit()
    writes += 1
    # Close the cursor
    cur.close()
    # Sleep for a short time to control the rate of insertion
    time.sleep(0.000078)  # 1/22000, 22000 writes per second 
```

In de bovenstaande code ziet de loop er nu iets anders uit. Ik groepeer de waardes per 50. Dit verbetert de schrijfsnelheid aanzienlijk: in 20 seconden zijn er nu 253,400 writes gedaan, 12,640 per seconden. Dat is in de buurt van de 22,000 writes per seconde. Er zit blijkbaar ontzettend veel overhead in het uitvoeren en committen van de query's. Als laatste test schrijf ik 100 datapunten per keer weg. Aangezien er in de limonadefabriek al 113 sensoren/actuatoren met hun datapunten zitten is dit een reële hoeveelheid data om weg te sturen per keer. 

Deze test levert 428,300 writes in 20 seconden, 21,415 per seconde. Dat is dicht genoeg in de buurt om de test succesvol te benoemen. Het samenvoegen van writes kan natuurlijk verder toegepast worden dan per unieke sensor. Na deze 20 seconden schrijven is de grootte van de database 35MB. Dit komt neer op 157GB per 24 uur. De opgeslagen data is nu wel 100 keer een DOUBLE PRECISION, die 64 bits lang is. In de praktijk is er per sensor maximaal een 32 bit waarde. Dit kan iets schelen, maar ik vermoed dat er al gauw gekeken moet worden naar nadere optimalisatie. Naarmate data ouder wordt kan ervoor gekozen worden om dit bijvoorbeeld langzaam weg te gooien (*Timescale Documentation | Data Retention*, z.d.). 

Ook kan de stakeholder zich wellicht afvragen of het nodig is om de data 200x per seconde op te slaan. Dit is nooit een harde eis geweest, slechts een aanname op basis van de cyclustijd van de IO-Link masters. Gegeven genoeg processorkracht en opslag is het dus mogelijk om dit te doen, dit voorbeeld draait namelijk op mijn bijna 6 jaar oude middenklasse laptop. 

## Conclusie

Het antwoord op de hoofdvraag is dus TimescaleDB, met wat optimalisatie in de manier waarop ik de INSERT-statements groepeer. TimescaleDB blijkt snel genoeg te zijn voor het verwerken van de writes en biedt de juiste features om een goede keuze te zijn voor het project. Wel moet er gekeken worden naar opslag-optimalisatie. 

## Bronnen

Foote, K. D. (2022, 15 september). *A Guide to Time Series Databases*. DATAVERSITY. https://www.dataversity.net/a-guide-to-time-series-databases/

*DB-Engines ranking*. (z.d.). DB-Engines. https://db-engines.com/en/ranking/time+series+dbms

*Timescale Documentation | About writing data*. (z.d.). https://docs.timescale.com/use-timescale/latest/write-data/about-writing-data/

*Timescale Documentation | Data retention*. (z.d.). https://docs.timescale.com/use-timescale/latest/data-retention/