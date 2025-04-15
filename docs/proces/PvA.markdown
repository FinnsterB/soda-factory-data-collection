

## Inhoudsopgave

[1 Inleiding 3](#inleiding)

[2 Achtergrond van het project 4](#achtergrond-van-het-project)

[3 Doelstelling, opdracht en op te leveren resultaten voor het bedrijf
5](#doelstelling-opdracht-en-op-te-leveren-resultaten-voor-het-bedrijf)

[4 Projectgrenzen 6](#projectgrenzen)

[5 Randvoorwaarden 6](#randvoorwaarden)

[6 Op te leveren producten en kwaliteitseisen
7](#op-te-leveren-producten-en-kwaliteitseisen)

[7 Ontwikkelmethoden 9](#ontwikkelmethoden)

[8 Projectorganisatie en communicatie
9](#projectorganisatie-en-communicatie)

[9 Planning 9](#planning)

[10 Risico's 9](#risicos)

## Inleiding

In dit document licht ik de planning van mijn afstudeerproject toe en
leg ik alle afspraken, grenzen, voorwaarden en eisen vast die nodig zijn
voor een succesvolle afronding. Gedurende het project gebruik ik het PvA
om steeds mijn volgende taken te bepalen. Zo zorg ik ervoor dat mijn
werkmethode inzichtelijk is voor mijzelf en de begeleiders.

In opdracht van MA-IT maak ik een embedded systeem dat gegevens
verzamelt van alle sensoren en actuatoren in een productielijn en de
mogelijkheid biedt om deze te analyseren en eventuele problemen te
diagnosticeren.

Dit document bevat de volgende hoofdstukken:

1.  **Inleiding**: Kleine opdrachtomschrijving en leeswijzer.

2.  **Achtergrond van het project**: Beschrijving van de organisatie,
    opdracht en relevante stakeholders.

3.  **Doelstelling, opdracht en op te leveren resultaten voor het
    bedrijf:** Gaat dieper in op de opdracht.

4.  **Projectgrenzen:** Beschrijft waar mijn project eindigt in termen
    van tijd en inhoud.

5.  **Randvoorwaarden:** Aan welke voorwaarden moet voldaan worden wil
    het project succesvol aflopen?

6.  **Ontwikkelmethoden:** Welke projectmethode gebruik ik?

7.  **Projectorganisatie en -communicatie:** Gegevens van belangrijke
    personen in het project en de afspraken daarmee.

8.  **Planning:** Wanneer vinden belangrijke gebeurtenissen, zowel van
    de projectmethode als in het afstudeertraject, plaats?

9.  **Risico's:** Welke risico's zijn er in het project en wat is hun
    impact?

## Achtergrond van het project

MyAutomation MA-IT is al sterk vertegenwoordigd in de industriële
automatisering binnen energietechniek, machinebouw en procestechniek.
Tot nu toe beperkt dit zich vooral tot de software engineering van
PLC-bestuurde installaties. Bij klanten zit veel interesse naar slimmer
diagnosticeren en anticiperen op potentiële gebreken en stilstand door
veroudering, slijtage of defecten aan de installaties. Sensoren worden
steeds slimmer, maar worden nog lang niet altijd toegepast met gebruik
van alle mogelijkheden. Moderne sensoren kunnen veel meer informatie
genereren dan hun basale signalen. PLC\'s zijn hiervoor geen geëigende
apparaten om deze \'overvloed\' aan informatie te verwerken. Welke
embedded controllers kunnen hiervoor wel ingezet worden?

## Doelstelling, opdracht en op te leveren resultaten voor het bedrijf

Om dit te onderzoeken gebruik ik de limonademachine van MA-IT. Deze
draait op een PLC die maar gelimiteerd sensorinformatie
opslaat/ontsluit. De sensoren op de installatie zijn echter van een
slimme variant die naast zijn primaire waarde(b.v. flow ja of nee) ook
dingen als temperatuur of druk meten. Daarnaast zijn de operation times
van de verschillende sensoren en actuatoren van belang om predictive
maintenance toe te passen. Al deze gegevens worden verstuurd met een
IO-link protocol en het is belangrijk om van alle types sensoren en
actuatoren de waarden uit te lezen. Dit wordt gedaan door een embedded
systeem dat ik zelf in moet richten die de gegevens wegschrijft naar een
database. Uiteindelijk moet er een soort dashboard komen waarin
zichtbaar is wat de status van elk onderdeel is: moet deze binnenkort
vervangen worden, wat zijn de meetwaarden enzovoorts.\
Om de sensoren en actuatoren te configureren moet er een
configuratiesysteem zijn. Dit kan bestaan uit een lijst of database van
sensoren en actuatoren en hun interfaces met daarin bijgehouden hoe hun
berichten uitgelezen moeten worden. Op deze manier is het een modulair
systeem dat aangepast kan worden naar de configuratie van verschillende
fabrieksprocessen.

## Projectgrenzen

Tijdens het project hanteer ik de onderstaande grenzen. Naast het
inbakenen van de projecttijd zorg ik er hier voor dat de
afstudeeropdracht niet te ver afwijkt van de competenties die bij mijn
opleiding Embedded Software Development horen.

|  			Beschrijving projectgrens 		                             |  			Toelichting 		                                                                                                                                                                                                                                                         |
|---------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|  			Het afstudeerproject is afgelopen op: 3 oktober 2025. 		 |  			Hiermee is de maximale looptijd van de afstudeerstage bereikt. In 			uitzonderlijke gevallen kan dit met maximaal 8 weken verlengd 			worden in overleg met de organisatie. 		                                                                                               |
|  			Ik ontwikkel geen PLC-software. 		                       |  			Dit past als Embedded Software Developer niet geheel bij mijn 			opleidingscompetenties en draagt dus niet bij aan het succesvol 			afstuderen. 		                                                                                                                           |
|  			Ik ontwikkel geen mobiele app. 		                        |  			Dit past ook niet bij de opleidingscompetenties. 		                                                                                                                                                                                                                    |
|  			Ik gebruik geen bestaande SCADA-software. 		             |  			Idem. 		                                                                                                                                                                                                                                                               |
|  			Ik ontwikkel geen cross-platform software. 		            |  			Afhankelijk van de microcontroller die ik kies zal ik in principe 			voor Linux ontwikkelen. Omdat de software in een “embedded” 			context ontwikkeld wordt en het niet de bedoeling is dat 			eindgebruikers dit zelf kunnen installeren. 		                                  |
|  			Ik ontwikkel geen eigen AI/ML modellen. 		               |  			Bij het ontwikkelen en trainen van een AI/ML model gaat heel veel 			tijd zitten in andere zaken dan het ontwerpen en implementeren van 			software, zoals het vergaren en voorbereiden van trainingsdata en 			het fine-tunen. Dit past niet bij de opleidingscompetenties. 		 |

## Randvoorwaarden

Om het project succesvol te laten verlopen moet er aan de volgende
randvoorwaarden voldaan worden.

-   Het opdrachtgever stelt een werkplek beschikbaar tussen 8.00 en
    18.00 gedurende de stageperiode.

-   De opdrachtgever biedt gedurende de stageperiode een begeleider die
    vakinhoudelijke kennis heeft.

-   De opdrachtgever zorgt bij de inrichting van het project dat de
    student in staat wordt gesteld inleverdeadlines van school te halen.

## Op te leveren producten en kwaliteitseisen

| **Product**        | **Kwaliteitseisen**                                                                                                                                                                                                 | **Benodigde activiteit**                                                                                                                                                                  | **Proceskwaliteit**                                          |
|--------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------|
| Onderzoeken        |                                                                                                                                                                                                                     |                                                                                                                                                                                            | - Onderzoek wordt voorgelegd aan begeleider voor feedback.    |
| Keuze type database| - Onderzoek is relevant voor het project.<br>- Onderzoek stelt criteria vast.<br>- Onderzoek vergelijkt meerdere alternatieven op basis van criteria.                                                             | - Vaststellen welke data in de database komt.<br>- Vaststellen hoeveel data in de database komt.<br>- Long list van databasetypes maken.<br>- Criteria opstellen.<br>- Keuze maken a.d.h.v. criteria. |                                                               |
| Protocollen: IO-Link/TCP-profinet | - Onderzoek is relevant voor het project.<br>- Onderzoek vergelijkt indien nodig methoden van het ophalen van data.                                                                                   | - Vaststellen hoe IO-Link werkt.<br>- Vaststellen hoe TCP-profinet werkt.<br>- Gegevens onderscheppen met een library.                                                                    |                                                               |
| Keuze embedded controller | - Onderzoek is relevant voor het project.<br>- Onderzoek stelt criteria vast.<br>- Onderzoek vergelijkt meerdere alternatieven op basis van criteria.                                                  | - Long list van embedded controllers maken.<br>- Criteria opstellen.<br>- Keuze maken a.d.h.v. criteria.                                                                                   |                                                               |
| Prototypes         |                                                                                                                                                                                                                     |                                                                                                                                                                                            |                                                               |
| Uitlezen sensordata en actuatorstatus met controller | - Controller kan zonder invloed op de PLC de gegevens uitlezen.<br>- Controller kan de maximale zend- en ontvangstcapaciteit van de PLC bijhouden.<br>- Geschreven in C/C++.<br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting. | - Resultaat van het protocollenonderzoek gebruiken.<br>- Testopstelling maken voor maximale capaciteits­test.<br>- Softwareontwerp maken.<br>- Software schrijven.<br>- Testen met testopstelling. |                                                               |
| Database           | - Kan de maximale output van de controller aan.<br>- Gedocumenteerd in SDD.                                                                                                                                        | - Database definiëren in DDL.<br>- Testdata invoeren.<br>- Bepalen welke query's handig zijn en deze vastleggen.                                                                          |                                                               |
| Predictive maintenance scheduler | - Kan o.b.v. analyse onderhoudsmomenten inplannen.<br>- Geschreven in C/C++.<br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting.                                              |                                                                                                                                                                                            |                                                               |
| Gebruikersinterface| - Biedt mogelijkheid om gegevens per sensor of actuator in te zien.<br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting.                                                                  |                                                                                                                                                                                            |                                                               |
| Configurator       | - Biedt een CRUD interface voor sensor en/actuatoren.<br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting.                                                                                  |                                                                                                                                                                                            |                                                               |
| Documentatie       |                                                                                                                                                                                                                     |                                                                                                                                                                                            |                                                               |
| SRS                | - Bevat een uitwerking van alle relevante hoofdstukken uit het SRS-template document (van Heesch, 2016a).<br>- Gebruikt MoSCoW-prioriteitsindeling voor de eisen.                                                 |                                                                                                                                                                                            |                                                               |
| SDD                | - Bevat een uitwerking van alle relevante hoofdstukken uit het SDD-template document (van Heesch, 2016b).                                                                   |                                                                                                                                                                                            |                                                               |
| Testdocumentatie   | - Bevat testcases die elke eis uit het SRS testen.<br>- Bevat een beschrijving van de unittests.                                                                                                                  |                                                                                                                                                                                            |                                                               |
| Handleidingen      | - Handleiding voor installatie van het systeem.<br>- Handleiding voor het gebruik van het systeem.<br>- Handleidingen omvatten de functionele eisen uit het SRS.                                                |                                                                                                                                                                                            |                                                               |
| Eindproduct        |                                                                                                                                                                                                                     |                                                                                                                                                                                            |                                                               |
| Geïntegreerd systeem | - Voldoet aan alle MUST-eisen in het SRS.<br>- Slagingspercentage unittesten is 100%.                                                                                     |                                                                                                                                                                                            |                                                               |


## Ontwikkelmethoden

Voor dit project gebruik ik RUP als projectmethode. Hierbij houd ik er
rekening mee dat RUP een groot aantal rollen biedt die ik in mijn eentje
niet ga kunnen vervullen en dat een groot deel van de ceremonies
daardoor ook afvallen.

## Projectorganisatie en communicatie

Tijdens mijn afstudeerperiode heb ik een aantal begeleiders:

Chris van Uffelen: Begeleider vanuit de opleiding,
<chris.vanuffelen@han.nl>.

Eduard de Grefte: Inhoudelijk begeleider van MA-IT,
<e.de.grefte@iaprofacademy.nl>.

Koen Sleurink: Inhoudelijk begeleider van MA-IT, <sleurink@ma-it.nl>.

Marc Waarle: Bedrijfsbegeleider van MA-IT, <waarle@ma-it.nl>.

De begeleiders van MA-IT zijn in principe altijd op locatie beschikbaar
en daar kan ik gewoon bij terecht als er vragen zijn.

## Planning

## Risico**'s**
