---
title: "![](logo.jpeg){width=\"0.7569444444444444in\"
  height=\"0.5104166666666666in\"}Plan van aanpak"
---

Inhoudsopgave

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

# Inleiding

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

# Achtergrond van het project

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

# Doelstelling, opdracht en op te leveren resultaten voor het bedrijf

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

# Projectgrenzen

Tijdens het project hanteer ik de onderstaande grenzen. Naast het
inbakenen van de projecttijd zorg ik er hier voor dat de
afstudeeropdracht niet te ver afwijkt van de competenties die bij mijn
opleiding Embedded Software Development horen.

  -------------------------- --------------------------------------------
  Beschrijving projectgrens  Toelichting

  Het afstudeerproject is    Hiermee is de maximale looptijd van de
  afgelopen op: 3 oktober    afstudeerstage bereikt. In uitzonderlijke
  2025.                      gevallen kan dit met maximaal 8 weken
                             verlengd worden in overleg met de
                             organisatie.

  Ik ontwikkel geen          Dit past als Embedded Software Developer
  PLC-software.              niet geheel bij mijn opleidingscompetenties
                             en draagt dus niet bij aan het succesvol
                             afstuderen.

  Ik ontwikkel geen mobiele  Dit past ook niet bij de
  app.                       opleidingscompetenties.

  Ik gebruik geen bestaande  Idem.
  SCADA-software.            

  Ik ontwikkel geen          Afhankelijk van de microcontroller die ik
  cross-platform software.   kies zal ik in principe voor Linux
                             ontwikkelen. Omdat de software in een
                             "embedded" context ontwikkeld wordt en het
                             niet de bedoeling is dat eindgebruikers dit
                             zelf kunnen installeren.

  Ik ontwikkel geen eigen    Bij het ontwikkelen en trainen van een AI/ML
  AI/ML modellen.            model gaat heel veel tijd zitten in andere
                             zaken dan het ontwerpen en implementeren van
                             software, zoals het vergaren en voorbereiden
                             van trainingsdata en het fine-tunen. Dit
                             past niet bij de opleidingscompetenties.

                             
  -------------------------- --------------------------------------------

# Randvoorwaarden

Om het project succesvol te laten verlopen moet er aan de volgende
randvoorwaarden voldaan worden.

-   Het opdrachtgever stelt een werkplek beschikbaar tussen 8.00 en
    18.00 gedurende de stageperiode.

-   De opdrachtgever biedt gedurende de stageperiode een begeleider die
    vakinhoudelijke kennis heeft.

-   De opdrachtgever zorgt bij de inrichting van het project dat de
    student in staat wordt gesteld inleverdeadlines van school te halen.

# Op te leveren producten en kwaliteitseisen

+----------------+----------------+-----------------+-----------------+
| **Product**    | **Kwa          | **Benodigde     | **Pr            |
|                | liteitseisen** | activiteit**    | oceskwaliteit** |
+----------------+----------------+-----------------+-----------------+
| Onderzoeken    |                |                 | \- Onderzoek    |
|                |                |                 | wordt           |
|                |                |                 | voorgelegd aan  |
|                |                |                 | begeleider voor |
|                |                |                 | feedback.       |
+----------------+----------------+-----------------+-----------------+
| Keuze type     | \- Onderzoek   | \- Vaststellen  |                 |
| database       | is relevant    | welke data in   |                 |
|                | voor het       | de database     |                 |
|                | project.       | komt.           |                 |
|                |                |                 |                 |
|                | \- Onderzoek   | \- Vaststellen  |                 |
|                | stelt criteria | hoeveel data in |                 |
|                | vast.          | de database     |                 |
|                |                | komt.           |                 |
|                | \- Onderzoek   |                 |                 |
|                | vergelijkt     | \- Long list    |                 |
|                | meerdere       | van             |                 |
|                | alternatieven  | databasetypes   |                 |
|                | op basis van   | maken.          |                 |
|                | criteria.      |                 |                 |
|                |                | \- Criteria     |                 |
|                |                | opstellen.      |                 |
|                |                |                 |                 |
|                |                | \- A.d.h.v.     |                 |
|                |                | criteria een    |                 |
|                |                | keuze maken.    |                 |
+----------------+----------------+-----------------+-----------------+
| Protocollen:   | \- Onderzoek   | \- Vaststellen  |                 |
| IO-Lin         | is relevant    | hoe IO-Link     |                 |
| k/TCP-profinet | voor het       | werkt.          |                 |
|                | project.       |                 |                 |
|                |                | \- Vaststellen  |                 |
|                | \- Onderzoek   | hoe             |                 |
|                | vergelijkt     | TCP-profinet    |                 |
|                | indien nodig   | werkt.          |                 |
|                | methoden van   |                 |                 |
|                | het ophalen    | \- Gegevens     |                 |
|                | van data.      | onderscheppen   |                 |
|                |                | met een         |                 |
|                |                | library.        |                 |
+----------------+----------------+-----------------+-----------------+
| Keuze embedded | \- Onderzoek   | \- Long list    |                 |
| controller     | is relevant    | van embedded    |                 |
|                | voor het       | controllers     |                 |
|                | project.       | maken.          |                 |
|                |                |                 |                 |
|                | \- Onderzoek   | \- Criteria     |                 |
|                | stelt criteria | opstellen.      |                 |
|                | vast.          |                 |                 |
|                |                | \- A.d.h.v.     |                 |
|                | \- Onderzoek   | criteria een    |                 |
|                | vergelijkt     | keuze maken.    |                 |
|                | meerdere       |                 |                 |
|                | alternatieven  |                 |                 |
|                | op basis van   |                 |                 |
|                | criteria.      |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Prototypes     |                |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Uitlezen       | \- Controller  | \- Resultaat    |                 |
| sensordata en  | kan zonder     | van het         |                 |
| actuatorstatus | invloed op de  | proto           |                 |
| met controller | PLC de         | collenonderzoek |                 |
|                | gegevens       | gebruiken.      |                 |
|                | uitlezen.      |                 |                 |
|                |                | \-              |                 |
|                | \- Controller  | Testopstelling  |                 |
|                | kan de         | maken voor      |                 |
|                | maximale zend  | maximale        |                 |
|                | en             | c               |                 |
|                | ont            | apaciteitstest. |                 |
|                | vangcapaciteit |                 |                 |
|                | van de PLC     | \-              |                 |
|                | bijhouden.     | Softwareontwerp |                 |
|                |                | maken.          |                 |
|                | \- Geschreven  |                 |                 |
|                | in C/C++.      | \- Software     |                 |
|                |                | schrijven.      |                 |
|                | \- Getest met  |                 |                 |
|                | unittests.     | \- Testen met   |                 |
|                |                | testopstelling. |                 |
|                | \-             |                 |                 |
|                | Gedocumenteerd |                 |                 |
|                | d.m.v. UML en  |                 |                 |
|                | toelichting.   |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Database       | \- Kan de      | \- Database     |                 |
|                | maximale       | definieren in   |                 |
|                | output van de  | DDL.            |                 |
|                | controller     |                 |                 |
|                | aan.           | \- Testdata     |                 |
|                |                | invoeren.       |                 |
|                | \-             |                 |                 |
|                | Gedocumenteerd | \- Bepalen      |                 |
|                | in SDD.        | welke querys    |                 |
|                |                | handig zijn en  |                 |
|                |                | deze            |                 |
|                |                | vastleggen.     |                 |
+----------------+----------------+-----------------+-----------------+
| Predictive     | \- Kan o.b.v.  |                 |                 |
| maintenance    | analyse        |                 |                 |
| scheduler      | onde           |                 |                 |
|                | rhoudsmomenten |                 |                 |
|                | inplannen.     |                 |                 |
|                |                |                 |                 |
|                | \- Geschreven  |                 |                 |
|                | in C/C++.      |                 |                 |
|                |                |                 |                 |
|                | \- Getest met  |                 |                 |
|                | unittests.     |                 |                 |
|                |                |                 |                 |
|                | \-             |                 |                 |
|                | Gedocumenteerd |                 |                 |
|                | d.m.v. UML en  |                 |                 |
|                | toelichting.   |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Gebu           | \- Biedt       |                 |                 |
| ikersinterface | mogelijkheid   |                 |                 |
|                | om gegevens    |                 |                 |
|                | per sensor of  |                 |                 |
|                | actuator in te |                 |                 |
|                | zien.          |                 |                 |
|                |                |                 |                 |
|                | \- Getest met  |                 |                 |
|                | unittests.     |                 |                 |
|                |                |                 |                 |
|                | \-             |                 |                 |
|                | Gedocumenteerd |                 |                 |
|                | d.m.v. UML en  |                 |                 |
|                | toelichting.   |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Configurator   | \- Biedt een   |                 |                 |
|                | CRUD interface |                 |                 |
|                | voor           |                 |                 |
|                | sensor         |                 |                 |
|                | en/actuatoren. |                 |                 |
|                |                |                 |                 |
|                | \- Getest met  |                 |                 |
|                | unittests.     |                 |                 |
|                |                |                 |                 |
|                | \-             |                 |                 |
|                | Gedocumenteerd |                 |                 |
|                | d.m.v. UML en  |                 |                 |
|                | toelichting.   |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Documentatie   |                |                 |                 |
+----------------+----------------+-----------------+-----------------+
| SRS            | \- Bevat een   |                 |                 |
|                | uitwerking van |                 |                 |
|                | alle relevante |                 |                 |
|                | hoofdstukken   |                 |                 |
|                | uit het        |                 |                 |
|                | SRS-te         |                 |                 |
|                | mplatedocument |                 |                 |
|                | (van Heesch,   |                 |                 |
|                | 2016a).        |                 |                 |
|                |                |                 |                 |
|                | \- Gebruikt    |                 |                 |
|                | MoSCoW-prior   |                 |                 |
|                | iteitsindeling |                 |                 |
|                | voor de eisen. |                 |                 |
+----------------+----------------+-----------------+-----------------+
| SDD            | \- Bevat een   |                 |                 |
|                | uitwerking van |                 |                 |
|                | alle relevante |                 |                 |
|                | hoofdstukken   |                 |                 |
|                | uit het        |                 |                 |
|                | SDD-templa     |                 |                 |
|                | tedocument(van |                 |                 |
|                | Heesch,        |                 |                 |
|                | 2016b).        |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Te             | \- Bevat       |                 |                 |
| stdocumentatie | testcases die  |                 |                 |
|                | elke eis uit   |                 |                 |
|                | het SRS        |                 |                 |
|                | testen.        |                 |                 |
|                |                |                 |                 |
|                | \- Bevat een   |                 |                 |
|                | beschrijving   |                 |                 |
|                | van de         |                 |                 |
|                | unittests.     |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Handleidingen  | \- Handleiding |                 |                 |
|                | voor           |                 |                 |
|                | installatie    |                 |                 |
|                | van het        |                 |                 |
|                | systeem.       |                 |                 |
|                |                |                 |                 |
|                | \- Handleiding |                 |                 |
|                | voor het       |                 |                 |
|                | gebruik van    |                 |                 |
|                | het systeem.   |                 |                 |
|                |                |                 |                 |
|                | \-             |                 |                 |
|                | Handleidingen  |                 |                 |
|                | omvatten de    |                 |                 |
|                | functionele    |                 |                 |
|                | eisen uit het  |                 |                 |
|                | SRS.           |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Eindproduct    |                |                 |                 |
+----------------+----------------+-----------------+-----------------+
| Geintegreerd   | \- Voldoet aan |                 |                 |
| systeem        | alle           |                 |                 |
|                | MUST-eisen in  |                 |                 |
|                | het SRS.       |                 |                 |
|                |                |                 |                 |
|                | \-             |                 |                 |
|                | Slag           |                 |                 |
|                | ingspercentage |                 |                 |
|                | unittesten is  |                 |                 |
|                | 100%.          |                 |                 |
+----------------+----------------+-----------------+-----------------+

# Ontwikkelmethoden

Voor dit project gebruik ik RUP als projectmethode. Hierbij houd ik er
rekening mee dat RUP een groot aantal rollen biedt die ik in mijn eentje
niet ga kunnen vervullen en dat een groot deel van de ceremonies
daardoor ook afvallen.

# Projectorganisatie en communicatie

Tijdens mijn afstudeerperiode heb ik een aantal begeleiders:

Chris van Uffelen: Begeleider vanuit de opleiding,
<chris.vanuffelen@han.nl>.

Eduard de Grefte: Inhoudelijk begeleider van MA-IT,
<e.de.grefte@iaprofacademy.nl>.

Koen Sleurink: Inhoudelijk begeleider van MA-IT, <sleurink@ma-it.nl>.

Marc Waarle: Bedrijfsbegeleider van MA-IT, <waarle@ma-it.nl>.

De begeleiders van MA-IT zijn in principe altijd op locatie beschikbaar
en daar kan ik gewoon bij terecht als er vragen zijn.

# Planning

# Risico**'s**
