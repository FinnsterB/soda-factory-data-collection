
# Plan van aanpak

## 1. Inhoudsopgave

- [Plan van aanpak](#plan-van-aanpak)
  - [1. Inhoudsopgave](#1-inhoudsopgave)
  - [2. Inleiding](#2-inleiding)
  - [3. Achtergrond van het project](#3-achtergrond-van-het-project)
  - [4. Doelstelling, opdracht en op te leveren resultaten voor het bedrijf](#4-doelstelling-opdracht-en-op-te-leveren-resultaten-voor-het-bedrijf)
  - [5. Projectgrenzen](#5-projectgrenzen)
  - [6. Randvoorwaarden](#6-randvoorwaarden)
  - [7. Op te leveren producten en kwaliteitseisen](#7-op-te-leveren-producten-en-kwaliteitseisen)
  - [8. Ontwikkelmethoden](#8-ontwikkelmethoden)
  - [9. Projectorganisatie en communicatie](#9-projectorganisatie-en-communicatie)
  - [10. Planning](#10-planning)
  - [11. Risico's](#11-risicos)
  - [12. Bronnen](#12-bronnen)


## 2. Inleiding

In dit document licht ik de planning van mijn afstudeerproject toe en leg ik alle afspraken, grenzen, voorwaarden en eisen vast die nodig zijn voor een succesvolle afronding. Gedurende het project gebruik ik het PvA om steeds mijn volgende taken te bepalen. Zo zorg ik ervoor dat mijn werkmethode inzichtelijk is voor mijzelf en de begeleiders.

In opdracht van MyAutomation MA-IT maak ik een embedded systeem dat gegevens verzamelt van alle sensoren en actuatoren in een productielijn en de mogelijkheid biedt om deze te analyseren voor "predictive maintenance" en productieoptimalisatie.

Dit document bevat de volgende hoofdstukken:

1.  **Inhoudsopgave**
   
2.  **Inleiding**: Kleine opdrachtomschrijving en leeswijzer.

3.  **Achtergrond van het project**: Beschrijving van de organisatie,
    opdracht en relevante stakeholders.

4.  **Doelstelling**, opdracht en op te leveren resultaten voor het
    bedrijf:** Gaat dieper in op de opdracht.

5.  **Projectgrenzen:** Beschrijft waar mijn project eindigt in termen
    van tijd en inhoud.

6.  **Randvoorwaarden:** Aan welke voorwaarden moet voldaan worden wil
    het project succesvol aflopen?

7.  **Ontwikkelmethoden:** Welke projectmethode gebruik ik?

8.  **Projectorganisatie en -communicatie:** Gegevens van belangrijke
    personen in het project en de afspraken daarmee.

9.  **Planning:** Wanneer vinden belangrijke gebeurtenissen, zowel van
    de projectmethode als in het afstudeertraject, plaats?

10. **Risico's:** Welke risico's zijn er in het project en wat is hun
    impact?

## 3. Achtergrond van het project

MyAutomation MA-IT is al sterk vertegenwoordigd in de industriële automatisering binnen energietechniek, machinebouw en procestechniek.
 Tot nu toe beperkt dit zich vooral tot de software engineering van PLC-bestuurde installaties. Bij klanten zit veel interesse naar slimmer diagnosticeren en anticiperen op potentiële gebreken en stilstand door veroudering, slijtage of defecten aan de installaties. Sensoren worden steeds slimmer, maar worden nog lang niet altijd toegepast met gebruik van alle mogelijkheden. Moderne sensoren kunnen veel meer informatie genereren dan hun basale signalen. PLC\'s kunnen deze informatie doorgaans niet allemaal verwerken. MA-IT wil een embedded oplossing aanbieden die dit wél kan. Het ontwerpen en implementeren hiervan is mijn afstudeerproject. 

## 4. Doelstelling, opdracht en op te leveren resultaten voor het bedrijf

Om dit te ontwikkelen gebruik ik de limonademachine van MA-IT. Deze draait op een PLC die maar gelimiteerd sensorinformatie opslaat/ontsluit. De sensoren op de installatie zijn echter van een slimme variant die naast zijn primaire waarde(b.v. flow ja of nee) ook dingen als temperatuur of druk meten. Daarnaast zijn de operation times van de verschillende sensoren en actuatoren van belang om predictive maintenance toe te passen. Al deze gegevens worden verstuurd met een IO-link protocol en Profinet en het is belangrijk om van alle types sensoren en actuatoren de waarden uit te lezen. Dit wordt gedaan door een embedded systeem dat ik zelf in moet richten die de gegevens wegschrijft naar een database en per sensor de operation times en andere relevante informatie bijhoudt. Dit systeem is dus meer dan alleen een doorgeefluik voor informatie. Om de extra informatie van de sensoren en actuatoren te configureren moet er een configuratiesysteem zijn. Uiteindelijk moet er een soort dashboard komen waarin zichtbaar is wat de status van elk onderdeel is: moet deze binnenkort vervangen worden, wat zijn de meetwaarden enzovoorts. Op deze manier is het een modulair systeem dat aangepast kan worden naar de configuratie van verschillende fabrieksprocessen. 

## 5. Projectgrenzen

Tijdens het project hanteer ik de onderstaande grenzen. Naast het inbakeren van de projecttijd zorg ik er hier voor dat de afstudeeropdracht niet te ver afwijkt van de competenties die bij mijn opleiding Embedded Software Development horen. 

|Beschrijving projectgrens|Toelichting|
|---|---|
|Het afstudeerproject is afgelopen op: 3 oktober 2025.|Hiermee is de maximale looptijd van de afstudeerstage bereikt. In uitzonderlijke gevallen kan dit met maximaal 8 weken verlengd worden in overleg met de organisatie.|
|Ik ontwikkel geen PLC-software.|Dit past als Embedded Software Developer niet geheel bij mijn opleidingscompetenties en draagt dus niet bij aan het succesvol afstuderen.|
|Ik ontwikkel geen mobiele app.|Dit past ook niet bij de opleidingscompetenties.|
|Ik ontwikkel geen cross-platform software.|Afhankelijk van de (micro)controller die ik kies zal ik in principe voor Linux of voor Windows ontwikkelen, niet allebei. Omdat de software in een “embedded” context ontwikkeld wordt en het niet de bedoeling is dat eindgebruikers dit zelf kunnen installeren.|
|Ik ontwikkel geen eigen AI/ML modellen.|Bij het ontwikkelen en trainen van een AI/ML model gaat heel veel tijd zitten in andere zaken dan het ontwerpen en implementeren van software, zoals het vergaren en voorbereiden van trainingsdata en het fine-tunen. Dit past niet bij de opleidingscompetenties. |

## 6. Randvoorwaarden

-   Om het project succesvol te laten verlopen moet er aan de volgende randvoorwaarden voldaan worden.
     -   Het opdrachtgever stelt een werkplek beschikbaar tussen 8.30 en 17.00 gedurende de stageperiode.
     -   De opdrachtgever biedt gedurende de stageperiode een begeleider die vakinhoudelijke kennis heeft.
     -   De opdrachtgever zorgt bij de inrichting van het project dat de student in staat wordt gesteld inleverdeadlines van school te halen.
     -   De opdrachtgever biedt waar nodig softwarelicenties en hardware voor de opdracht.
     -   De opdrachtgever biedt waar nodig gereedschap voor de opdracht.

## 7. Op te leveren producten en kwaliteitseisen

Ieder product dat ik ga opleveren heeft één of meerdere kwaliteitseisen. Deze staan in de onderstaande tabel beschreven. Om tot een kwalitatief voldoende product te komen moeten aan deze eisen voldaan worden. Dit doe ik door minimaal de stappen in de kolom "Benodigde activiteit" uit te voeren en mij daarbij te houden aan de "Proceskwaliteitseisen". De producten zijn ingedeeld in een aantal categorieën en wanneer er in de rij van de categorieaanduiding een veld is ingevuld dan geldt dat veld voor alle producten in die categorie.

| **Product**        | **Kwaliteitseisen**| **Benodigde activiteit**| **Proceskwaliteitseisen**|
|:--|---|---|---|
| **Onderzoeken**| | | **- Onderzoeksdocumenten worden in versiebeheer bijgehouden.<br>- Onderzoek wordt voorgelegd aan begeleider voor feedback.** |
| Keuze type database/platform| - Onderzoek is relevant voor het project.<br>- Onderzoek stelt criteria vast.<br>- Onderzoek vergelijkt meerdere alternatieven op basis van criteria.<br>-Onderzoek geeft een eenduidig resultaat waarop verder gebouwd kan worden. | - Vaststellen welke data in de database komt.<br>- Vaststellen hoeveel data in de database komt.<br>- Long list van databasetypes maken.<br>- Criteria opstellen.<br>- Keuze maken a.d.h.v. criteria. |- Voorleggen aan vakinhoudelijke medewerker wanneer het onderzoeksresultaat bekend is.|
| Protocollen: IO-Link/TCP-profinet | - Onderzoek is relevant voor het project.<br>- Onderzoek vergelijkt indien nodig methoden van het ophalen van data. <br>- Onderzoek biedt de basis voor het prototype "Uitlezen sensordata en actuatorstatus met controller". | - Vaststellen hoe IO-Link werkt.<br>- Vaststellen hoe TCP-profinet werkt.<br>- Gegevens onderscheppen met een library.| - Gesprek met collega's/begeleiders die meer verstand hebben van dit soort systemen voeren om aan informatie te komen.|
| Keuze embedded controller | - Onderzoek is relevant voor het project.- Onderzoek stelt criteria vast.<br>- Onderzoek vergelijkt meerdere alternatieven op basis van criteria.<br>- Onderzoek geeft een eenduidig resultaat waarop verder gebouwd kan worden. | - Long list van embedded controllers maken.<br>- Criteria opstellen.<br>- Keuze maken a.d.h.v. criteria.||
| **Prototypes** |||**- Prototypes worden als branches in het versiebeheer opgenomen om in de constructiefase geïntegreerd te worden.<br>- Prototypes worden wanneer ze klaar zijn gedemonstreerd in een Milestone-meeting.**|
| Uitlezen sensordata en actuatorstatus met controller | - Controller kan zonder invloed op de PLC de gegevens uitlezen.<br>- Controller buiten de cyclische datastromen van de PLC gegevens opvragen van de sensoren.<br>- Geschreven in C/C++.<br>- Code wordt objectgeorienteerd geschreven. <br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting. | - Eisen opvragen  en vastleggen in het SRS. <br>- Resultaat van het protocollenonderzoek gebruiken.<br>- Testopstelling maken voor maximale capaciteits­test.<br>- Softwareontwerp maken.<br>- Software schrijven.<br>- Testen met testopstelling. |- Controleren of de geïmplementeerde en geteste functionaliteit overeenkomt met de eisen in het SRS. <br>|
| Database/platform  | - Kan de maximale output van de controller aan.<br>- Gedocumenteerd in SDD.| - Database definiëren in DDL.<br>- Testdata invoeren.<br>- Bepalen welke query's handig zijn en deze vastleggen.||
| Gebruikersinterface| - Biedt mogelijkheid om gegevens per sensor of actuator in te zien.<br>- Biedt mogelijkheid om ingeplande onderhoudsmomenten in te zien.<br>- Code wordt objectgeorienteerd geschreven mits de gekozen programmeertaal dit toelaat. <br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting.|- Keuze maken voor interfacemethode, Web of desktop-applicatie. <br>- Softwareontwerp maken. <br>- Software schrijven. <br>- Unittests schrijven en uitvoeren|- Controleren of de geïmplementeerde en geteste functionaliteit overeenkomt met de eisen in het SRS. <br/>|
| Configurator       | - Biedt een CRUD interface voor sensor en/actuatoren.<br>- Code wordt objectgeorienteerd geschreven mits de gekozen programmeertaal dit toelaat.<br>- Getest met unittests.<br>- Gedocumenteerd d.m.v. UML en toelichting.| - Uitzoeken welke gegevens van de sensoren relevant zijn zoals ID, typeaanduiding, welke data ze doorgeven.<br>- Gegevensvelden bedenken voor predictive maintenance. Welke soorten onderhoud zijn relevant? Vastleggen in SRS.<br>- Softwareontwerp maken.<br>-Software schrijven.<br>-Unittests schrijven. |- Controleren of de geïmplementeerde en geteste functionaliteit overeenkomt met de eisen in het SRS. <br/>|
| **Documentatie**       ||||
| Plan van Aanpak |- Bevat een uitwerking van alle hoofdstukken uit "Toelichting op PvA V4.0"(Praktijkbureau AIM, 2022)|||
| SRS                | - Bevat een uitwerking van alle relevante hoofdstukken uit het SRS-template document (van Heesch, 2016a).<br>- Gebruikt MoSCoW-prioriteitsindeling voor de eisen.<br>-Voldoet aan AIM-controlekaart.|- Dit is een lopend document, waar gedurende de hele ontwikkeling aan wordt gewerkt. <br>- De eisen aan het op te leveren systeem worden in een vroeg stadium verzameld. <br> |- Door opdrachtgever laten lezen.|
| SDD                | - Bevat een uitwerking van alle relevante hoofdstukken uit het SDD-template document (van Heesch, 2016b).<br>-Voldoet aan AIM-controlekaart.|- Ook dit is een lopen document, waar gedurende de onwikkeling steeds meer ontwerpkeuzes in zullen verschijnen. <br>- Elk prototype wordt vastgelegd||
| Testdocumentatie   | - Bevat testcases die elke eis uit het SRS testen.<br>- Bevat een beschrijving van de unittests.<br>-Voldoet aan AIM-controlekaart.|- Opstellen van testcases a.d.h.v. de requirements uit het SRS. <br>- Uitleg over de unittests schrijven. ||
| Handleidingen      | - Handleiding voor installatie van het systeem.<br>- Handleiding voor het gebruik van het systeem.<br>- Handleidingen omvatten de functionele eisen uit het SRS.<br>-Voldoen aan AIM-controlekaart.| - Nagaan of er een template voor handleidingen wordt gehanteerd. <br>- Alle functionaliteit in het SRS uitwerken met screenshots en begeleidende tekst. | - Laten doorlezen door iemand uit het bedrijf voor feedback. |
| **Eindproduct**        ||||
| Geïntegreerd systeem | - Voldoet aan alle MUST-eisen in het SRS.<br>- Alle unittesten moeten slagen.|- Integreren van de verschillende prototypes.<br>- Testcases doorlopen uit de testdocumentatie.||
| Afstudeerverslag|- Beschrijft hoe mijn afstudeerstage verloopt. <br>- Volgt de "Schrijfwijzer Afstudeerverslag"(Hogeschool van Arnhem en Nijmegen, 2022). |- Wanneer een van de bovenstaande producten voorlopig af is voeg ik inhoud aan het verslag toe. <br>- Richting het eind van het afstudeertraject schrijf ik de managementsamenvatting. <br>- | |


## 8. Ontwikkelmethoden

Voor dit project gebruik ik RUP als projectmethode. Dit doe ik omdat RUP vrij schaalbaar is en een handige projectindeling biedt. Het werk dat ik in dit project moet verrichten past goed in de fases. 

### Inceptiefase

In de inceptiefase staat het helder krijgen van het project centraal. De doelen, scope en procedure worden vastgesteld(*RUP op Maat* , z.d.) en daaruit volgt dit Plan Van Aanpak. 

### Elaboratiefase



### Constructiefase



### Transitiefase



- Het schrijven van het PvA en het vergaren van de eisen van het te realiseren systeem vallen in de inceptiefase. 
- Daarna vallen de onderzoeken en de prototypen in de elaboratiefase. 
- Het uitbreiden en integreren van de prototypen wordt in de constructiefase gedaan.
- Het laatste deel van de testen, het schrijven van de overdracht(handleidingen, testdocumentatie).



## 9. Projectorganisatie en communicatie

Tijdens mijn afstudeerperiode heb ik een aantal begeleiders: Chris van Uffelen: Begeleider vanuit de opleiding, <chris.vanuffelen@han.nl>.
 Eduard de Grefte: Inhoudelijk begeleider van MA-IT, <e.de.grefte@iaprofacademy.nl>.
 Koen Sleurink: Inhoudelijk begeleider van MA-IT, <sleurink@ma-it.nl>.
 Marc Waarle: Bedrijfsbegeleider van MA-IT, <waarle@ma-it.nl>. Opdrachtgever tijdens mijn stage.
 De begeleiders van MA-IT zijn in principe altijd op locatie beschikbaar en daar kan ik gewoon bij terecht als er vragen zijn.

## 10. Planning



## 11. Risico's

## 12. Bronnen

*RUP op Maat* . (2011). https://www.rupopmaat.nl/naslagsite2011/index.html

Praktijkbureau AIM. (2022). Toelichting op PVA 4.0. In *OnderwijsOnline*.

Van Heesch, U. (2016a). Software Requirements Specification Template. In *OnderwijsOnline*.

Van Heesch, U. (2016b). Software Design Description Template. In *OnderwijsOnline*.
