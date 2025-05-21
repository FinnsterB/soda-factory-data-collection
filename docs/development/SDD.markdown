# System Design Description

## Inleiding





## Architectuuroverzicht





## Ontwerpomschrijving in detail

### Deployment diagram

![](../../out/docs/development/deployment/Deployment_diagram.png)

In het bovenstaande deploymentdiagram staat een abstracte weergave van het systeem, met daarin de node "Analyser". Op deze node draait de software die ik moet realiseren en die is opgebouwd uit de volgende componenten:

**Profinet Sniffer**

De Profinet Sniffer leest met behulp van *libtins* of *libpcap* de Profinet-pakketten van de netwerkkaart. Omdat de netwerkkaart veel meer berichten binnenkrijgt dan alleen Profinet moet er gefilterd worden op de juiste soort berichten. De berichten worden dan aangeboden aan de Data Handler met behulp van een queue. 

**Device Data Storage**

Deze database houdt bij welke Profinet-devices er op het netwerk zitten. Voor iedere device zijn een aantal zaken van belang:

- MAC-adres
- DeviceID
- VendorID
- Datapoints met offsets

Deze gegevens worden bepaald op basis van de aangeleverde GSDML files door de GSDML-parser en de [Profinet-DCP berichten](../research/profinet-io-link.markdown#data-offsets). 

**Data Handler**

De Data Handler plukt de Profinet-pakketten als het ware uit elkaar op basis van de Device Data Storage. De berichten hebben een vaste lengte en met de byte-offset moet het mogelijk zijn om de data te interpreteren. Er zit uiteraard een verschil tussen de IO-Link masters en bijvoorbeeld de B&R Bus Controller. De Data Handler biedt een interface om de meest recente data op te halen, en schrijft de data zelf weg naar de Historical IO Database.

**Historical IO Data**

Deze database bevat de historische IO-data van de hele installatie. De sensoren en actuatoren hebben ieder een ID die overeenkomt met de Device Data, en de waarden die door de Data Handler worden weggeschreven worden hierin alleen opgeslagen met een Sensor ID en een timestamp. Deze database is een *time series* database (In dit geval TimescaleDB, uit onderzoek [Database](../research/database.markdown#conclusie)) die is geoptimaliseerd voor het opslaan van reeksen data in de tijd. Dit maakt het sneller om de data op te halen en weg te schrijven.

**GSDML Parser**

