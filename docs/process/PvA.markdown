# Plan van aanpak

**Begrippenlijst**

| Term  | Definitie                                                    |
| ----- | ------------------------------------------------------------ |
| SRS   | System Requirements Specification; document waar de eisen aan het te realiseren systeem in staan vastgelegd. |
| SDD   | Software Design Description; document waar het softwareontwerp en ontwerpkeuzes in staan vastgelegd. |
| RUP   | Rational Unified Process; ontwikkelmethode, bedacht door Rational Software, die bedoeld is om te schaalbaar en aanpasbaar te zijn naar de eisen van verschillende projecten en organisaties. |
| MA-IT | MA-IT MyAutomation; het bedrijf waar mijn afstudeerstage plaatsvindt. |



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
    - [Inceptiefase](#inceptiefase)
    - [Elaboratiefase](#elaboratiefase)
    - [Constructiefase](#constructiefase)
    - [Transitiefase](#transitiefase)
  - [9. Projectorganisatie en communicatie](#9-projectorganisatie-en-communicatie)
    - [Reviews](#reviews)
  - [10. Planning](#10-planning)
  - [11. Risico's](#11-risicos)
  - [12. Bronnen](#12-bronnen)


## 2. Inleiding

In dit document licht ik de planning van mijn afstudeerproject toe en leg ik alle afspraken, grenzen, voorwaarden en eisen vast die nodig zijn voor een succesvolle afronding. Gedurende het project gebruik ik het plan van aanpak om steeds mijn volgende taken te bepalen. Zo zorg ik ervoor dat mijn werkmethode inzichtelijk is voor mijzelf en de begeleiders.

In opdracht van MA-IT MyAutomation maak ik een embedded systeem dat gegevens verzamelt van alle sensoren en actuatoren in een productielijn en de mogelijkheid biedt om deze te analyseren voor "predictive maintenance" en productieoptimalisatie.

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

MA-IT MyAutomation  is al sterk vertegenwoordigd in de industriële automatisering binnen energietechniek, machinebouw en procestechniek. Tot nu toe beperkt dit zich vooral tot de software engineering van PLC-bestuurde installaties. Bij klanten zit veel interesse naar slimmer diagnosticeren en anticiperen op potentiële gebreken en stilstand door veroudering, slijtage of defecten aan de installaties. Sensoren worden steeds slimmer, maar worden nog lang niet altijd toegepast met gebruik van alle mogelijkheden. Moderne sensoren kunnen veel meer informatie genereren dan hun basale signalen. PLC\'s kunnen deze informatie doorgaans niet allemaal verwerken. MA-IT wil een embedded oplossing aanbieden die dit wél kan. Het ontwerpen en implementeren hiervan is mijn afstudeerproject. 

## 4. Doelstelling, opdracht en op te leveren resultaten voor het bedrijf

Het doel van deze afstudeeropdracht is om, met een embedded systeem, van bestaande fabrieksinstallaties zoveel mogelijk gegevens te verzamelen en daarmee predictive maintenance en andere optimalisaties toe te passen. 

Om dit embedded systeem te ontwikkelen gebruik ik de limonademachine van MA-IT. Deze draait op een Siemens PLC die maar gelimiteerd sensorinformatie opslaat/ontsluit. De sensoren op de installatie zijn echter van een slimme variant die naast zijn primaire waarde(b.v. flow ja of nee) ook dingen als temperatuur of druk meten. Al deze gegevens worden verstuurd met een IO-link protocol en Profinet en het is belangrijk om van alle types sensoren en actuatoren de waarden uit te lezen. Het systeem dat ik moet implementeren zal de gegevens wegschrijven naar een database en per sensor of actuator verschillende parameters bijhouden. Bijvoorbeeld de operation times van de verschillende sensoren, hoe vaak een klep open en dicht is gegaan en nog meer andere gegevens zijn van belang om predictive maintenance toe te passen. Het is dus meer dan alleen een doorgeefluik voor informatie. Om de extra informatie van de sensoren en actuatoren te configureren moet er een configuratiesysteem zijn. Uiteindelijk moet er een soort dashboard komen waarin zichtbaar is wat de status van elk onderdeel is: moet deze binnenkort vervangen worden, wat zijn de meetwaarden enzovoorts. Op deze manier is het een modulair systeem dat aangepast kan worden naar de configuratie van verschillende fabrieksprocessen. 

Hieronder volgt een lijst met op te leveren resultaten. Deze worden in hoofdstuk 7 verder toegelicht met concrete kwaliteitseisen en acties.

**Analyse/onderzoeken(met behulp van de ICT Research Methods):** <br>
• Berichten van sensoren uitlezen: tussenlaag voor bedenken<br>
• Keuze van embedded controller <br>
• Keuze van type database <br>
• Keuze van opzet database <br>
• Protocollen: io-link/tcp-profinet <br>
• Prototype embedded controller die de sensoren uitleest<br>
• Prototype database<br>
• Prototype gebruikersinterface en configurator<br>
**Softwareontwikkeling:** <br>
• SRS <br>
• SDD <br>
• Testdocumentatie<br>
• Handleidingen <br>
• Geintegreerd systeem<br>



## 5. Projectgrenzen

Tijdens het project hanteer ik de onderstaande grenzen. Naast het inbakeren van de projecttijd zorg ik er hier voor dat de afstudeeropdracht niet te ver afwijkt van de competenties die bij mijn opleiding Embedded Software Development horen. 

|Beschrijving projectgrens|Toelichting|
|---|---|
|Het afstudeerproject is afgelopen op: 3 oktober 2025.|Hiermee is de maximale looptijd van de afstudeerstage bereikt. In uitzonderlijke gevallen kan dit met maximaal 8 weken verlengd worden in overleg met de organisatie.|
|Ik ontwikkel geen PLC-software.|Dit past als Embedded Software Developer niet geheel bij mijn opleidingscompetenties en draagt dus niet bij aan het succesvol afstuderen.|
|Ik ontwikkel geen mobiele app.|Dit past ook niet bij de opleidingscompetenties.|
|Ik ontwikkel geen cross-platform software.|Afhankelijk van de (micro)controller die ik kies zal ik in principe voor Linux of voor Windows ontwikkelen, niet allebei. Omdat de software in een “embedded” context ontwikkeld wordt en het niet de bedoeling is dat eindgebruikers dit zelf kunnen installeren.|
|Ik ontwikkel geen eigen AI/ML modellen.|Bij het ontwikkelen en trainen van een AI/ML model gaat heel veel tijd zitten in andere zaken dan het ontwerpen en implementeren van software, zoals het vergaren en voorbereiden van trainingsdata en het fine-tunen van het model. Dit past niet bij de opleidingscompetenties. |

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
| Plan van Aanpak |- Bevat een uitwerking van alle hoofdstukken uit "Toelichting op PvA V4.0"(Praktijkbureau AIM, 2022)|- Vergaren van de opdracht door spreken met bedrijfsbegeleider. <br>- Uitkiezen projectmethode.<br>-||
| SRS                | - Bevat een uitwerking van alle relevante hoofdstukken uit het SRS-template document (van Heesch, 2016a).<br>- Gebruikt MoSCoW-prioriteitsindeling voor de eisen.<br>-Voldoet aan AIM-controlekaart.|- Dit is een lopend document, waar gedurende de hele ontwikkeling aan wordt gewerkt. <br>- Het projectdomein wordt vastgesteld.<br>- De eisen aan het op te leveren systeem worden in een vroeg stadium verzameld. <br>- De eisen worden verder gespecificeerd d.m.v. Use Cases. <br>- |- Door opdrachtgever laten lezen.|
| SDD                | - Bevat een uitwerking van alle relevante hoofdstukken uit het SDD-template document (van Heesch, 2016b).<br>-Voldoet aan AIM-controlekaart. <br>- Is een logische uitwerking van de eisen uit het SRS. |- Ook dit is een lopend document, waar gedurende de ontwikkeling steeds meer ontwerpkeuzes in zullen verschijnen. <br>- Elk prototype vastleggen in een of meerdere diagrammen van zowel de programmastructuur als het gedrag. <br>-Elk van die diagrammen voorzien van begeleidende tekst waarmee de ontwerpkeuzes worden toegelicht. <br>|- Per gerealiseerd onderdeel laten controleren door inhoudelijk begeleider.|
| Testdocumentatie   | - Bevat testcases die elke eis uit het SRS testen.<br>- Bevat een beschrijving van de unittests.<br>-Voldoet aan AIM-controlekaart.|- Opstellen van testcases a.d.h.v. de requirements uit het SRS. <br>- Uitleg over de unittests schrijven. ||
| Handleidingen      | - Handleiding voor installatie van het systeem.<br>- Handleiding voor het gebruik van het systeem.<br>- Handleidingen omvatten de functionele eisen uit het SRS.<br>-Voldoen aan AIM-controlekaart.| - Nagaan of er een template voor handleidingen wordt gehanteerd. <br>- Alle functionaliteit in het SRS uitwerken met screenshots en begeleidende tekst. | - Laten doorlezen door iemand uit het bedrijf voor feedback. |
| **Eindproduct**        ||||
| Geïntegreerd systeem | - Voldoet aan alle MUST-eisen in het SRS.<br>- Alle unittesten moeten slagen.|- Integreren van de verschillende prototypes.<br>- Testcases doorlopen uit de testdocumentatie.||
| Afstudeerverslag|- Beschrijft hoe mijn afstudeerstage verloopt. <br>- Volgt de "Schrijfwijzer Afstudeerverslag"(Hogeschool van Arnhem en Nijmegen, 2022). |- Wanneer een van de bovenstaande producten voorlopig af is voeg ik inhoud aan het verslag toe. <br>- Richting het eind van het afstudeertraject schrijf ik de managementsamenvatting. <br>- | |


## 8. Ontwikkelmethoden

Voor dit project gebruik ik RUP als projectmethode. Dit doe ik omdat RUP vrij schaalbaar is en een handige projectindeling biedt. Het werk dat ik in dit project moet verrichten past goed in de fases. 

### Inceptiefase

In de inceptiefase staat het helder krijgen van de opdracht centraal. De doelen, scope en procedure worden vastgesteld(*RUP op Maat* , z.d.) en daaruit volgt dit Plan Van Aanpak. Daarnaast bespreek ik alvast de eisen aan het product met de opdrachtgever en leg ik deze vast in het SRS. 

### Elaboratiefase

In de elaboratiefase doe ik onderzoek naar de benodigde technieken en bouw ik prototypen voor de belangrijke grote onderdelen van de opdracht. De onderzoeken vormen de grondslag voor het ontwerp van deze prototypen in het SDD. Daarna realiseer ik het ontwerp. De prototypen bewijzen in principe dat de technieken werken en bruikbaar zijn voor het project. Hiermee heb ik een gevalideerde architectuur. 

### Constructiefase

In de constructiefase knoop ik de prototypen aan elkaar tot een geïntegreerd systeem. Hierbij breid ik het SDD uit zodat het een volledig naslagwerk wordt van de codestructuur en de bijbehorende ontwerpkeuzes. Ook breid ik hier de tests uit, deze zijn nu niet meer per prototype maar kunnen het hele systeem van de ene tot de andere kant testen. Zo kan er aan de ene kant testdata ingevoerd worden en aan de andere kant gekeken worden of dit op de juiste manier verwerkt wordt door het systeem. Dit levert een nagenoeg compleet en finaal systeem op dat slechts overgedragen hoeft te worden.

### Transitiefase

In de transitiefase wordt het systeem klaargemaakt voor overdracht. In deze fase repareer ik de laatste bugs en gebeuren er verder slechts kleine dingetjes aan de software. Daarnaast maak ik de benodigde handleidingen voor de installatie en gebruik van het systeem. De opdrachtgever en/of andere stakeholders moet zelf uit de voeten kunnen met de opgeleverde documentatie. Ook is bewezen dat het systeem van voldoende kwaliteit is d.m.v. de testdocumentatie. Er blijkt uit de rapportage dat de tests geslaagd zijn.



## 9. Projectorganisatie en communicatie

Tijdens mijn afstudeerperiode heb ik een aantal begeleiders: Chris van Uffelen: Begeleider vanuit de opleiding, <chris.vanuffelen@han.nl>.
 Eduard de Grefte: Inhoudelijk begeleider van MA-IT, <e.de.grefte@iaprofacademy.nl>.
 Koen Sleurink: Inhoudelijk begeleider van MA-IT, <sleurink@ma-it.nl>.
 Marc Waarle: Bedrijfsbegeleider van MA-IT, <waarle@ma-it.nl>. Opdrachtgever tijdens mijn stage.
 De begeleiders van MA-IT zijn in principe altijd op locatie beschikbaar en daar kan ik gewoon bij terecht als er vragen zijn.

### Reviews

Tijdens het project is het van belang dat ik af en toe inhoudelijke feedback ontvang van mijn begeleiders. Daarom wil ik een soort milestone-vergadering houden op het moment dat een van de deelproducten klaar is. Deze staan in de planning in het volgende hoofdstuk. 

## 10. Planning

In de onderstaande tabel staan gebeurtenissen met betrekking tot inleverdeadlines en projectindeling. De planning volgt de RUP-projectmethode en de benodigde gebeurtenissen daarvoor staan ook in de tabel.

| Datum | Gebeurtenis                                                  | Beschrijving van gebeurtenis                                 |
| ----- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 14-4  | Start inceptiefase                                           | Op deze dag begint de inceptiefase en zal ik beginnen met werken aan het plan van aanpak. |
| 25-4  | Inleveren plan van aanpak(concept)                           | Deadline inleveren plan van aanpak. Hierna wordt er feedback op gegeven en een advies over de opdracht. |
| 28-4  | Meivakantie                                                  | Op deze dag begint de meivakantie voor school. De docenten zullen niet beschikbaar zijn. |
| 23-5  | Inleveren plan van aanpak(definitief)                        | Deadline inleveren definitieve versie plan van aanpak.       |
| 26-5  | Start elaboratiefase                                         | Op deze dag begint de elaboratiefase en begin ik met de onderzoeken. |
| 28-5  | Milestone: Keuze database/platform gemaakt.                  | Ik streef ernaar om op deze dag dit onderzoek af te ronden en het resultaat te overleggen. |
| 2-6   | Milestone: IO-link/Profinet                                  | Ik streef ernaar om op deze dag dit onderzoek af te ronden en een werkend voorbeeld te hebben. Dit is nog geen prototype. |
| 6-6   | Milestone: Keuze (micro)controller                           | Ik streef ernaar om op deze dag een keuze te hebben gemaakt m.b.t. de gebruikte (micro)controller. |
| 13-6  | Milestone: Prototype uitlezen sensor- en actuatordata met controller | Ik streef ernaar op deze dag een demo van het prototype te geven. |
| 18-6  | Milestone: Prototype database/platform                       | Ik streef ernaar op deze dag een demo van het prototype te geven. |
| 25-6  | Milestone: Gebruikersinterface                               | Ik streef ernaar op deze dag een demo van het prototype te geven. |
| 2-7   | Milestone: Configurator                                      | Ik streef ernaar op deze dag een demo van het prototype te geven. |
| 3-7   | Start constructiefase                                        | Op deze dag begint, mits alle milestones geweest zijn, de constructiefase en daarmee de integratie van alle onderdelen. |
| 10-7  | Placeholder: Use Case ? afgerond                             | Placeholder voor wanneer het SRS verder is uitgewerkt. In de constructiefase zal ik proberen per usecase of per eis te werken. |
| 14-7  | Begin HAN-zomervakantie                                      | Deze week begint volgens het HAN-jaarrooster de zomervakantie. De docenten zullen niet beschikbaar zijn. |
| 18-8  | Eind HAN-zomervakantie                                       | Vanaf vandaag is de zomervakantie afgelopen en zijn de docenten weer beschikbaar. |
| 22-8  | Inleveren definitief eindverslag voor feedback.              | Dit is de deadline voor het inleveren van mijn eindverslag voor feedback. |
| 1-9   | Start transitiefase                                          | Op deze dag begint, mits de vorige fasen zijn afgerond de transitiefase en zal ik beginnen aan het schrijven van handleidingen, het uitvoeren van de laatste tests en de overdracht. |
| 19-9  | Inleveren definitief eindverslag                             | Dit is de laatste deadline voor het eindverslag.             |

## 11. Risico's

Tijdens mijn afstudeerproject zijn er een aantal risico's. Dit zijn situaties die onverhoopt invloed hebben op de loop van het project. In dit hoofdstuk probeer ik van tevoren zoveel mogelijk risico's te onderkennen en hier uitwijkstrategieën en tegenmaatregelen voor te bedenken. Ook geef ik per risico de een inschatting van de kans dat de situatie zich voordoet en een een inschatting van de impact. 

| Risico                         | Datum van onderkenning | Impact | Kans | Tegenmaatregel                                               | Uitwijkstrategie                                             |
| ------------------------------ | ---------------------- | ------ | ---- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Hardware opstelling gaat kapot | 17-4                   | Laag   | Laag | - Reservehardware regelen van tevoren<br>- Voorzichtig omgaan met de hardware. | - Reservehardware inzetten.<br>-Vervangende hardware bestellen.<br> |
| Eigen laptop gaat kapot        | 17-4                   | Middel | Laag | - Reservelaptop regelen van tevoren.<br>- Cloudplatform(GitHub) gebruiken als versiebeheer.<br>-Bijhouden welke lokale tooling/software wordt gebruikt. | -Reservelaptop gebruiken.<br>                                |



## 12. Bronnen

*RUP op Maat* . (2011). https://www.rupopmaat.nl/naslagsite2011/index.html

Praktijkbureau AIM. (2022). Toelichting op PVA 4.0. In *OnderwijsOnline*.

Van Heesch, U. (2016a). Software Requirements Specification Template. In *OnderwijsOnline*.

Van Heesch, U. (2016b). Software Design Description Template. In *OnderwijsOnline*.
