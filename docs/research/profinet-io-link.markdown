# Onderzoek Profinet/IO-Link

## Begrippen

| Begrip | Beschrijving |
| ------ | ------------ |
|        |              |
|        |              |
|        |              |



## Inleiding

Voor het ophalen van de vereiste data moet ik gegevens van de fieldbus van de installatie halen. De Soda Factory heeft als fieldbus Profinet, alle sensoren en actuatoren (apparaten) communiceren hiermee met de PLC. Naast sensoren en actuatoren zitten er IO-Link masters aan. Een IO-Link master is een Profinet-apparaat dat meerdere sensoren en actuatoren aanstuurt. Zo kan er in een installatie een groep sensoren en actuatoren die bij elkaar in de buurt zitten aangestuurd worden met een master, zodat er slechts korte kabels van de sensoren naar de master hoeven. Er loopt dan een enkele lange Profinet-kabel van de master naar de regelkast. Dit systeem ziet er dan als volgt uit:

![](../../out/docs/research/profinet-io-link-diagram/profinet-io-link-diagram.png)



De sensordata wordt cyclisch opgehaald van de IO-link master. Voor dit onderzoek moet ik er dus achter komen hoe ik aan die sensordata kan komen. Profinet ondersteunt daisy-chainen van apparaten. Welke interfaces bieden de IO-Link masters en kan ik een computer op de Profinet-bus aansluiten?  De onderzoeksvragen worden beantwoord door middel van de HBO-ICT research methods. 

## Hoofdvraag en deelvragen

Voor dit onderzoek is de hoofdvraag: "Hoe kan ik de vereiste gegevens(Stakeholder_definitie_en_meetpuntenbepaling) ophalen uit de installatie?". 

Om daar achter te komen moet ik de volgende deelvragen beantwoorden:

1. Wat voor interfaces worden er door de verschillende apparaten geboden voor dataontsluiting? (Literature study)
2. Welke interfaces daarvan zijn bruikbaar? (Literature study)
3. Hoe onderschep ik pakketten die over Profinet verstuurd worden? (Literature study)
4. Hoe haal ik de vereiste sensordata uit de Profinet-pakketten? (Literature, Lab)



## Deelvraag 2: Over welke interfaces beschikken de apparaten?

De IFM AL1303 en AL1900 IO-Link masters zijn hoofdzakelijk gemaakt om met Profinet te communiceren maar beschikken ook over een IoT port die een REST API ontsluit (*AL1303 - IO-Link Master met Profinet-interface - Ifm*, z.d.). Deze REST API biedt toegang tot de precieze sensorwaarden en eventuele digitale in- en uitgangen. 

Nadeel is dat deze IoT ports per master beschikbaar zijn, dus dat er naar iedere master nog een kabel gelegd moet worden. De kabels moeten allemaal naar een switch en dan pas kunnen alle IO-Link masters bereikt worden. Dan heb ik alleen de waarden uit de IO-Link masters, en dus geen status van het ventieleiland, die alleen via Profinet communiceert. 

Ook zit er een IO-Controller in de regelkast. Veel PLC-gestuurde apparaten zijn aangestuurd met een digitaal signaal en kunnen dus *aan* of *uit* zijn. In de Soda Factory worden alle pompen en verwarmingselementen op deze manier aangestuurd. Ze hebben een output nodig om ze aan te zetten en een input voor het feedbacksignaal. De IO-Controller wordt, net als het ventieleiland alleen cyclisch door Profinet bestuurd. 

Er zijn dus twee beschikbare interfaces:

- Profinet (Alle apparaten, alleen cyclisch)
- IoT-Port met REST interface (Alleen de IO-Link masters, ook buiten cyclus)



## Deelvraag 3: Welke interfaces zijn bruikbaar?

De IoT ports zijn voor het doel wat ik voor ogen heb niet geheel geschikt; ze vereisen namelijk aanpassingen aan de installatie. Er moet een extra switch in komen en er moet UTP kabel gelegd worden naar alle IO-Link masters. Daarnaast mis ik wat data, omdat sommige onderdelen zoals het ventieleiland en enkele relais aangestuurd worden met Profinet. Ook deze data heb ik uiteindelijk nodig voor analyse, vandaar dat ik liever niet voor deze optie kies.

De PLC verstuurt alle cyclische data over Profinet. Profinet gebruikt een strak gedefinieerd netwerk, waarbij de PLC als *controller* fungeert en alle devices(sensoren, actuatoren, IO-Link masters) alleen met de *controller* communiceren(McMillan, 2018). 

Een manier om data uit te lezen is door een Profinet *supervisor* te implementeren. Bestaande voorbeelden van Profinet supervisors zijn de software die vanuit fabrikanten geleverd wordt om PLC's te programmeren en te configureren, zoals bijvoorbeeld TIA Portal. Deze software maakt gebruik van Profinet-drivers van Siemens, en die is in principe alleen onder licentie beschikbaar voor apparaatfabrikanten (*Industrial Operations X Documentation*, z.d.). Hetzelfde geldt voor de Profinet Community Stack van Profi International. 

Om zonder Profinet-driver alsnog aan de cyclische data te komen kan ik de Profinet-pakketten onderscheppen en zelf parsen. In principe laat ik het bestaande netwerk hiermee intact. 

## Deelvraag 4: Hoe onderschep ik pakketten die over Profinet verstuurd worden?

Profinet gebruikt Ethernet en TCP/IP. TCP/IP wordt echter alleen gebruikt voor configuratieberichten die bij elke start-up verstuurd worden om het netwerk te configureren. De cyclische data tussen de devices en de PLC gebruikt het Profinet RT protocol. Dit protocol gebruikt geen IP, alleen de MAC-adressen van de apparaten en kan dus alleen gelezen worden door apparaten op het netwerk die het juiste MAC-adres hebben. Door te testen met Wireshark kon ik door aan de switch in de regelkast aan te sluiten:

![](Profinet_network.png)

Door op deze manier het netwerk te sniffen kan ik echter *geen* Profinet RT pakketten zien. Alleen zo nu en dan een PN-DCP of een PN-PTCP bericht, die gebruikt worden om het netwerk in te stellen, en om Delay_Request te sturen. Deze berichten zijn niet interessant voor mij omdat ze geen data bevatten. 

Om wel aan de Profinet RT berichten te komen moet ik ervoor zorgen dat deze berichten bij mijn computer komen, ongeacht het verschillende MAC-adres. Hiervoor zat ik te denken aan een Ethernet TAP(Test Access Point), die al het verkeer naar mijn laptop doorstuurt(*Test Access Point (TAP)*, z.d.). Deze zijn erg duur en gespecialiseerd, dus niet heel realistisch om voor dit project te gebruiken. In plaats van de TAP kan ik een *managed* switch gebruiken die de mogelijkheid biedt voor port-mirroring(M, Waarle, persoonlijke communicatie, 12 mei 2025). Bij port-mirroring worden alle pakketten gekopieerd en uit een zogenaamde *monitor* port gestuurd. Een apparaat op die port kan dus al het netwerkverkeer zien, zelfs als het non-IP verkeer betreft. 

Voor deze test heeft Marc een managed switch ter beschikking gesteld. Door deze tussen de PLC en de rest van het netwerk aan te sluiten en de ports te mirroren naar de monitor-port moet het mogelijk zijn om de Profinet RT pakketten te zien ondanks dat mijn MAC-adres anders is. Dit zit als volgt aangesloten:

![](Profinet_network_managed.png)

Met deze testopstelling lukt het om Profinet RT pakketten te onderscheppen. De IO-data is zichtbaar in een blok van 40 bytes, alleen is deze nog niet ingedeeld. Welke data bij welke IO-Link sensor hoort kan ik nog niet vaststellen:

![](40-bytes.png)

## Deelvraag 5: Hoe haal ik de vereiste sensordata uit de Profinet-pakketten?

#### Profinet-RT pakketten

De opgehaalde Profinet RT-pakketten zijn opgebouwd uit de eerste 2 lagen van het OSI-model(Bowne, 2019). De andere Profinet-pakketten gebruiken wel TCP/IP. Om de PLC met alle andere apparaten te laten communiceren is een apparaatconfiguratie vereist. De PLC moet namelijk ook weten welke bytes van ieder gegeven Profinet-bericht bij welke sensor horen. Deze configuratie wordt gedaan middels een GSDML-bestand, ook wel GSD(General Station Description) genoemd. Deze bestanden zijn voor elk Profinet apparaat beschikbaar, en worden dus gebruikt om de PLC in te stellen.

Wireshark heeft een ingebouwde Profinet-decoder die ook gebruik maakt van de GSDML-bestanden. Wanneer ik de GSDML bestanden gebruik die bij de IO-Link masters horen dan kan ik de data inderdaad per sensor zien. Wanneer ik dit vergelijk met dezelfde sensor opgevraagd met de IoT interface dan komt de data overeen:

![](WiresharkvsIoT.png)

De sensordata zit verstopt in deze bits. Gek genoeg zit er in het Profinet-pakket nog een byte achteraan, "a0", met onbekende functie. Wanneer dit consistent is, kan ik die gewoon achterwege laten bij het ophalen van data. Dit moet nog getest worden. Bij het ventieleiland is dit niet het geval:

![](first-valve-off.png)

​							Bovenstaande afbeelding heeft alle kleppen uit.

![](first-valve-on.png)

​							Bovenstaande afbeelding heeft de eerste klep aan.



#### Data-offsets

Aan het begin van een power-cycle vindt er tussen de Profinet controller(PLC) en de Profinet-devices(IO-Link masters, ventieleiland) een soort handshake plaats waarin wat relevante configuratiedata gestuurd wordt. De GSDML-bestanden bevatten iedere mogelijke configuratie die een apparaat kan hebben, maar de daadwerkelijke ingestelde configuratie wordt in die handshake-berichten gestuurd. De handshake ziet er als volgt uit:



## Bronnen

*Test Access Point (TAP)*. (z.d.). https://www.felser.ch/profinet-manual/pn_test-access-point-(tap).html

McMillan, K. (2018, 15 juni). *Components: device, controller, Supervisor - PROFINET University*. PROFINET University. https://profinetuniversity.com/profinet-basics/components-device-controller-supervisor/

Bowne, M. (2019, 1 maart). *Network Reference Model - PROFINET University*. PROFINET University. https://profinetuniversity.com/industrial-automation-ethernet/network-reference-model/

*Industrial Operations X Documentation*. (z.d.). https://docs.industrial-operations-x.siemens.cloud/r/en-us/v3.2.0/profinet-driver/intro/licensing

*AL1303 - IO-Link Master met Profinet-interface - ifm*. (z.d.). https://www.ifm.com/nl/nl/product/AL1303