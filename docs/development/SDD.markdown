# System Design Description

## Inleiding

Dit document omschrijft het ontwerp van de gerealiseerde analysesoftware voor de Soda Factory. Deze software moet de sensordata van de Soda factory verkrijgen door de Profinet-fieldbus uit te lezen. Deze data moet opgeslagen worden in een historische database en met een gebruikersinterface inzichtelijk zijn voor een eindgebruiker. De volledige opdracht staat omschreven in het Plan van Aanpak. 

Met behulp van UML-diagrammen wordt de structuur en het gedrag van de software toegelicht. Dit gebeurt in de volgende hoofdstukken:

#TODO Leeswijzer



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
- Datatype van elke datapoint

Deze gegevens worden bepaald op basis van de aangeleverde GSDML files door de GSDML-parser en de [Profinet-DCP berichten](../research/profinet-io-link.markdown#data-offsets). 

**Data Handler**

De Data Handler plukt de Profinet-pakketten als het ware uit elkaar op basis van de Device Data Storage. De berichten hebben een vaste lengte en met de byte-offset moet het mogelijk zijn om de data te interpreteren. Er zit uiteraard een verschil tussen de IO-Link masters en bijvoorbeeld de B&R Bus Controller. De Data Handler biedt een interface om de meest recente data op te halen, en schrijft de data zelf weg naar de Historical IO Database.

**Historical IO Data**

Deze database bevat de historische IO-data van de hele installatie. De sensoren en actuatoren hebben ieder een ID die overeenkomt met de Device Data, en de waarden die door de Data Handler worden weggeschreven worden hierin alleen opgeslagen met een Sensor ID en een timestamp. Deze database is een *time series* database (In dit geval TimescaleDB, uit onderzoek [Database](../research/database.markdown#conclusie)) die is geoptimaliseerd voor het opslaan van reeksen data in de tijd. Dit maakt het sneller om de data op te halen en weg te schrijven.

**GSDML Parser**

De GSDML Parser moet de Profinet-configuratie bestanden verwerken en daaruit halen hoe de Profinet-apparaten hun berichten sturen. Dit is cruciaal voor het uitvinden waar de juiste bytes in de Profinet-pakketten verstopt zitten. De gebruiker van het systeem moet deze bestanden aanleveren, ze zijn door de fabrikanten gemaakt. Deze bestanden zijn ook nodig voor het PLC-programmeren in TIA-portal van Siemens. De benodigde data wordt in de Device Data Storage opgeslagen.

**User Interface**

De User Interface biedt visualisatie aan de gebruiker. Deze visualisatie biedt de mogelijkheid om verschillende sensoren met elkaar te vergelijken en verschillende tijdpunten met elkaar te vergelijken. 

### Ontwerp Profinet Sniffer

De techniek achter de Profinet Sniffer staat beschreven in het onderzoek Profinet/IO-Link. De Profinet Sniffer moet twee soorten berichten uitlezen: de Profinet connect requests en de Profinet Real Time IO messages. Uit de Connect requests kan een groot deel van de Profinet systeemconfiguratie gehaald worden. 

#### Klassendiagram

![](../../out/docs/development/pn_sniffer/pn_sniffer_class.png)

De Profinet-package biedt een model van de Profinet-fieldbus zoals die relevant is voor de opdracht. 

**SystemConfiguration**

De SystemConfiguration klasse geeft aan welke Profinet Devices er in de productielijn zitten. Deze klasse (todo) biedt (de)serializatie van de gegevens van de Profinet Devices. Wanneer het systeem een Profinet Connect message ziet, wordt de HandleConnect() functie aangeroepen. Deze functie maakt een PNDevice aan die de payload van de Connect message gebruikt om zijn verschillende membervariabelen in de vullen. Uiteindelijk wordt er gecheckt of de PNDevice al bestaat, in welk geval de *nieuwe* configuratie de plaats inneemt van de oude.

**PNMaster**

De PNMaster is een apparaat in het Profinet-netwerk dat de Devices aanstuurt. In vrijwel alle gevallen is dit een PLC. In deze context biedt de PNMaster-klasse slechts een paar gegevens die nodig zijn om de Profinet Realtime-IO berichten in te delen. Dit is de naam van het apparaat voor de GUI en het MAC-adres om in te zien welke berichten *van* de PLC komen en welke berichten *naar* de PLC gaan.

**PNDevice**

De PNDevice-klasse is een representatie van de Profinet-configuratie van een Device. Deze klasse biedt de gegevens om de Realtime-IO payload van deze Profinet Device uit te lezen. De verschillende *structs* die direct en indirect aan PNDevice toebehoren volgen de officiele Profinet-benaming zoals ze ook in de GSDML-bestanden en Wireshark worden weergegeven. 

**Structs**

PNDevice heeft verschillende structs waar zijn configuratie in verdeeld staat. Deze structs volgen de structuur van de Profinet Connect messages en zijn dus generiek voor iedere Profinet device. De structuur van deze berichten is complex en vereist een uitgebreide parser. 

**IOCRBlockReq:**

**API_IO_Data:**

**IOCS:**

**IO_Data_Object:**

**ExpectedSubmoduleBlockReq:**

**API_Module_Info:**

**Submodule:**



#### Sequencediagram



### Ontwerp Device Data Storage





### Ontwerp GSDML Parser





### Ontwerp Data Handler



