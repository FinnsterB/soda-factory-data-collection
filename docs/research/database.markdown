# Onderzoek Database



## Inleiding

In dit document licht ik mijn onderzoek naar een geschikte database toe. De [opdracht](../process/PvA.markdown#4-doelstelling-opdracht-en-op-te-leveren-resultaten-voor-het-bedrijf) staat beschreven in het PvA.



IP van IO-link master: 169.254.254.160.

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

Voor de hoofdvraag gebruik ik de antwoorden op de deelvragen en multi-criteria decision making.



## Deelvraag 1: Wat voor data moet er worden opgeslagen?

Deze vraag vereist zowel op het gebied van eisen een antwoord, als op het praktische vlak. Om de eis van dit onderdeel vast te stellen moet ik weten of mijn systeem pre-processing op de data moet uitvoeren. 

Stel dat er een heel simpel systeem is dat bestaat uit een watertoevoer met 1 klep met 1 flowsensor. Wanneer de klep aangestuurd wordt om open te gaan, dan duurt het heel even voordat het water gaat stromen. Deze tussentijd is relevant voor de stakeholder. Moet ik dan de tussentijd opslaan en om welke klep en sensor het gaat(pre-processing), of gewoon timestamped data?

De stakeholder heeft gekozen voor de tweede methode. De verwerking en interpretatie van de data wordt op een latere plek in de sequentie gedaan. Op deze manier gaat er geen data verloren die wellicht alsnog handig was. 

Praktisch gezien: Welke sensoren zitten er op de installatie? Hiervoor heb ik de IO-lijst die bij het PLC-programmeren is gebruikt. Hierop staat van alle sensoren en actuatoren wat voor merk, welk model en wat voor datatype(hoeveelheid bytes) ze hebben. 

Volgens de IO-lijst zijn de meeste sensoren en actuatoren aangestuurd of uitgelezen met een binaire waarde. Dit zijn de kleppen en hun feedbacksensoren, levelsensoren voor vloeistof in de tanks en de pompen. In totaal zijn dit 93 bits. 

Daarnaast beschikken de IO-link sensoren over preciezere data: 2, 4 of 8 bytes. Dit zijn 20 sensoren in de installatie. Deze sensoren meten temperatuur, flowrate of druk. Hoeveel opslag dit uiteindelijk gebruikt hangt af van de indeling van de DB.



## Deelvraag 2: Hoeveel data moet er worden opgeslagen?

Wanneer ik een IO-link master van de Soda Factory benader via zijn IoT-Port, dan geeft deze een handige webpagina terug met wat globale waarden: Wat voor sensor zit er op welke poort en wat is de cyclustijd van die port. Dit blijkt gemiddeld zo'n 5ms te zijn. In het ideale geval kan ik dus ongeveer elke 5ms data ophalen van de IO-Link masters. 

Stel dat ik alle data wil opslaan, dan moet ik 200x per seconde alle sensorwaarden van de hele installatie wegschrijven. Dat betekent dat 113*200, oftewel 22600 writes per *seconde* in het ergste geval. Wanneer ik de sensorwaarden echter opspaar en groepeer dan kan dit aantal verminderd worden.



## Deelvraag 3: Welke soorten opslag zijn gemaakt voor het soort data en de hoeveelheid ervan?

Aangezien de database gebruikt wordt voor sensorwaarden in de tijd is het handig om een "time series database" te gebruiken(Foote, 2022). De website [db-engines.com](https://db-engines.com) heeft een uitgebreide lijst waarin verschillende databases staan. Deze lijst is vooral op populariteit gesorteerd(*DB-Engines Ranking*, z.d.), wat voor mijn doeleind niet perse relevant is, maar wel handig. Hoe populairder een soort database is, hoe meer online ondersteuning er ook voor is. De populariteit zal dus als tie-breaker functioneren. 

Uit mijn vooronderzoek blijkt dat er een Profinet driver voor de real-time Linux kernel is van [Siemens](https://support.industry.siemens.com/cs/document/109974538/profinet-driver-v3-2-pnconfiglib-v1-5-download-software-package?dti=0&lc=en-NL). Deze is in C++ geimplementeerd, en gebruikt de Real Time Linux-kernel. Daarom zijn een C of C++ API en Linux-ondersteuning vereist voor de database. Zo kan de hele codebase van het project C++ blijven en dat maakt het builden en testen makkelijker. Verder moet de database een open source licentie hebben zodat ik hem mag gebruiken.

De volgende "time series databases" zijn beschikbaar en zijn de populairste:

| Naam            | Ondersteunt C/C++ API | Ondersteunt Linux | Open source licentie |
| --------------- | --------------------- | ----------------- | -------------------- |
| InfluxDB        | Nee                   | Ja                | Ja                   |
| Prometheus      | Nee                   | Ja                | Ja                   |
| Kdb             | Ja                    | Ja                | Nee                  |
| Graphite        | Nee                   | Ja                | Ja                   |
| **TimescaleDB** | Ja                    | Ja                | Ja                   |
| QuestDB         | Nee                   | Ja                | Ja                   |

TimescaleDB komt hieruit als enige die aan alle eisen voldoet. Dit is een extentie op PostgreSQL en biedt dezelfde C interface als PostgreSQL waardoor het goed bruikbaar is voor mijn project. TimescaleDB biedt een aantal optimalisaties voor het opslaan en ophalen van timestamped data.



## Conclusie



## Bronnen

Foote, K. D. (2022, 15 september). *A Guide to Time Series Databases*. DATAVERSITY. https://www.dataversity.net/a-guide-to-time-series-databases/

*DB-Engines ranking*. (z.d.). DB-Engines. https://db-engines.com/en/ranking/time+series+dbms