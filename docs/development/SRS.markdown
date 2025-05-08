# Software Requirements Specification

- [Software Requirements Specification](#software-requirements-specification)
- [Inleiding](#inleiding)
- [Domeinmodel](#domeinmodel)
- [Usecase-beschrijvingen](#usecase-beschrijvingen)
- [Overige functionele requirements](#overige-functionele-requirements)
- [Niet-functionele requirements](#niet-functionele-requirements)
- [Bronnen](#bronnen)


# Inleiding

In dit document leg ik vast wat de gestelde eisen zijn aan mijn afstudeeropdracht. Dit omvat zowel de functionele- als niet-functionele eisen. De eisen krijgen een prioriteit aangewezen door middel van MoSCoW-prioritering. Op deze manier is duidelijk welke eisen het belangrijkst zijn en welke ik dus als eerste implementeer. Om meer inzicht te krijgen in de benodigde werking van de software zijn sommige eisen uitgewerkt in de vorm van Use Cases. 

De opdracht wordt beschreven in H4 van het Plan Van Aanpak. Kort samengevat: er moet een embedded systeem ontwikkeld worden dat alle sensor- en actuatordata opvangt, analyseert(met behulp van een IIOT-Platform) en deze data en de analyse weergeeft aan een eindgebruiker. 

In het SRS wordt vaak het woord "sensoren" gebruikt als aanduiding voor "sensoren en actuatoren". Hier weet ik nog geen goede benaming aan te geven.

## Actors

De actors die van dit systeem gebruik gaan maken zijn de volgende:

### Productiemanager

De productiemanager houdt zich bezig met de optimalisatie van de productielijn en verlangt een bepaald soort gegevens.

### Technische dienst

De technische dienst houdt zich bezig met het onderhoud van de productielijn en verlangt een bepaald soort gegevens.

### Installateur

De installateur zal het systeem installeren en instellen. 

## Omgeving

In de regel bouw ik voor dit project een implementatie voor de limonadefabriek bij MA-IT. Deze beschikt over een Siemens PLC die met Profinet en IO-Link met zijn sensoren en actuatoren communiceert. De limonadefabriek is ruwweg opgedeeld in twee onderdelen: de productiekant en de CIP(Cleaning-in-Place)-installatie. 

### Productiekant van de installatie

De productie gebeurt in de grote mengtank die vrij centraal staat aan de installatie. Deze mengtank beschikt over twee gewone ingangen, een viertal kleine ingangen voor siroop, een interne sproeier en een uitgang. De uitgang van de tank kan met kleppen met de afvoerleiding gekoppeld worden, of naar een pomp. De pomp kan op zijn beurt naar de koolzuurtank pompen of weer terug de mengtank in. Door het voortdurend terugpompen naar de mengtank wordt de siroop met het water gemengd.

### CIP-installatie

De schoonmaak van het hele systeem wordt gefaciliteerd door de CIP-installatie. Deze is complexer dan de hele productiekant van de installatie en bestaat uit twee tanks, drie grote pompen en twee kleine doseerpompen voor chemicaliën. Hier beschikken de tanks over verwarmingselementen en evenals aan de productiekant kan de inhoud rondgepompt worden om te mengen. 

De uitvoer van beide tanks is aangesloten aan een pomp die de schoonmaakvloeistof naar de productietank pompt. Uiteraard kan er, door de juiste kleppen te schakelen, gekozen worden of de CIP-tanks hun inhoud mengen of naar de productietank sturen. Wanneer dit gebeurt is het de bedoeling dat het schoonmaakmiddel een aantal keer wordt rondgepompt in de productietank met gebruik van de sproeier. 

### Fieldbus voor sensoren en actuatoren

Alle sensoren en actuatoren zitten met Profinet aangesloten aan de PLC. De kleppen zijn op luchtdruk gestuurd door een ventieleiland. Deze stuurt luchtdruk naar de gewenste kleppen op basis van een bitpatroon. Ook deze komt van de Profinet-verbinding.

### Regelkast

Deel van de installatie is de regelkast. Hier zit onder andere de PLC, verschillende voedingen en schakelrelais gemonteerd. Deze regelkast is voorzien van een DIN-rail en kabelgoten. Het mooiste is om hier gebruik van te maken met mijn systeem.



## Ontwerp- en implementatiebeperkingen

Het systeem moet eenvoudig in een regelkast van een productielijn ingebouwd kunnen worden. In de regel bouw ik voor dit project een implementatie voor de limonadefabriek bij MA-IT. Deze beschikt over een Siemens PLC die met Profinet en IO-Link met zijn sensoren en actuatoren communiceert. Profinet is een fieldbus op basis van TCP/IP en gebruikt Ethernet als fysieke laag. Dit betekent dat ik vrijwel elke soort PC kan aansluiten, zolang die maar Ethernet ondersteunt. Nice-to-haves zijn wel dat deze PC gevoed kan worden met 24V en op een DIN-rail gemonteerd kan worden. 

## Productfuncties

Om de productfuncties per actor duidelijk te maken heb ik een usecase-diagram gemaakt. Om het diagram leesbaar te houden zijn bepaalde usecases gegroepeerd in de blokjes **Informatietoegang** en **Configuratietoegang**. 

![](../../out/docs/development/main_UCD/main_UCD.png)

Het systeem biedt informatie aan de *productiemanager* en de *technische dienst*. Deze actors moeten beide kunnen zien of de productielijn nog goed draait, of er waarschuwingen zijn en in het geval van calamiteiten wellicht terugkijken naar historische gegevens. Deze inhoud wordt op in een venster in de gebruikersinterface weergegeven. 

De instelmogelijkheid van het systeem hoeft niet bereikbaar te zijn voor de *productiemanager* maar wel voor de *installateur*. Zo kan de *installateur* een werkend systeem opleveren. Tevens kan de *installateur* ook bij de installatie van het systeem het analyseplatform instellen. Het analyseplatform wordt hoogstwaarschijnlijk een bestaand IIOT-platform, dat is waarom het in het SRS als secundaire actor wordt beschouwd.

Hieronder staat per use case een brief description:

**Inzien sensoren**

Wanneer de gebruiker(technische dienst, installateur) het configuratiepaneel opent krijgt deze een lijst met sensoren te zien mits deze zijn aangemaakt.

**Aanmaken sensoren**

De gebruiker kan een sensor toevoegen aan de persistente lijst van sensoren en daarbij een aantal parameters invullen zoals een naam, hoe de sensor verbonden is met de controller(precieze parameters moeten blijken uit onderzoek), en in welk datatype de sensor rapporteert. 

**Aanpassen sensoren**

Hetzelfde als "Aanmaken sensoren" alleen zijn de velden al ingevuld met de bestaande data. De bestaande sensor wordt overschreven.

**Verwijderen sensoren**

De gebruiker kan een specifieke sensor verwijderen uit de lijst. 

**Inzien meetwaarden realtime**

Per ingestelde sensor kan de gebruiker zien wat de huidige meetwaarde is. Dit wordt weergegeven in het hoofdvenster van het programma. De meetwaarde wordt opgehaald door de controller. 

**Inzien meetwaarden-historie**

Per ingestelde sensor kan de historie van meetwaarden opgehaald worden. Dit wordt weergegeven in het hoofdvenster van het programma. De meetwaarden-historie is afkomstig uit de database van het analyseplatform.

**Inzien analysewaarschuwingen**

De gebruiker ziet in het hoofdvenster een lijst met waarschuwingen over de betreffende productielijn. 

**Aanleveren analysewaarschuwingen**

Het analyseplatform heeft een interface of integratie met de controller waarmee het platform zijn waarschuwingen kan delen op het moment dat er een afwijking wordt gesignaleerd. 

**Instellen analyseplatform**

Om het analyseplatform te kunnen benaderen moeten er bepaalde zaken ingesteld worden zoals authenticatie, API-sleutels en servergegevens. 



# Domeinmodel

Het domein voor dit project bestaat hoofdzakelijk uit een bestaande productielijn die beschikt over een aantal sensoren en actuatoren. Deze hebben ieder een status, staan ze aan/uit, hoe staan ze ingesteld en nog meer. De sensoren in het bijzonder hebben data: de meetwaarden. De sensoren en actuatoren zitten via een Fieldbus(Profinet) aan de PLC aangesloten en dat is waar ons systeem ook terechtkomt. Onze Controller bevat allerlei onderdelen die gerealiseerd moeten worden: De Configurator, Gebruikersinterface en een integratie met een IIOT-Platform. 

![](../../out/docs/development/domain/domain.png)

Uiteindelijk is het de bedoeling dat ons systeem een analysemogelijkheid biedt van verschillende datapunten. De datapunten die opgehaald moeten worden zijn als volgt(uit bijlage Stakeholder_definitie_en_meetpuntenbepaling):

**CIP-tanks**

- Vulgraad (te bepalen middels de druktransmitter)
- Temperatuur
- Status van de circulatiepomp (meetpunt in de PLC; aan of uit)
- Debietmeting in de circulatieleiding
- Aansturing én status van de bodemklep (meetpunt in de PLC; aangestuurd ‘open’ en terugmelding open/dicht uit de IOlink master)

**CIP-transportleiding**

- Status van de circulatiepomp (meetpunt in de PLC; aan of uit)
- Debietmeting in de transportleiding
- Temperatuur van het medium in de transportleiding

**Productietank**

- Vulgraad (te bepalen middels de druktransmitter)
- Temperatuur in de tank
- Temperatuur in de circulatieleiding
- Status van de circulatiepomp (meetpunten in de PLC; aan of uit én het bitpatroon waarmee de snelheid wordt opgegeven)
- Debietmeting in de circulatieleiding
- Debietmeting in de leiding naar carbonisatie
- Aansturing én status van alle kleppen (meetpunt in de PLC; aangestuurd ‘open’ en terugmelding open/dicht uit de IOlink master)

**Carbonisatie tank**

- Druk in het vat
- Aansturing én status van de bodemklep/uitgifteklep (meetpunt in de PLC; aangestuurd ‘open’ en terugmelding open/dicht uit de IOlink master)
- Status van aansturing van de koolzuur toevoerklep(meetpunt in de PLC; aangestuurd 'open')





# Usecase-beschrijvingen

De functionele eisen van het systeem worden weergegeven als fully dressed use cases. Deze bieden per use case een uitgebreide beschrijving van de verantwoordelijkheden van het systeem op het moment dat een actor iets wil. De template voor deze fully dressed use cases komt uit het boek Applying UML and Patterns(Larman, z.d.). Alle use cases die in het diagram in hoofdstuk Productfuncties worden hier weergegeven in fully-dressed vorm.

### Inzien sensoren

**Level:** Configuratietoegang

**Primary actor:** Technische dienst, installateur

**Stakeholders and interests:**



**Preconditions:**

Het systeem is aan en volledig opgestart. Er zijn sensoren toegevoegd met use case "Aanmaken sensoren".

**Success guarantee:**

De lijst met ingestelde sensoren is zichtbaar en doorzoekbaar.

**Main success scenario:**

1. Gebruiker opent configuratiepaneel.
2. Systeem toont lijst met bestaande sensoren.

**Extensions:**

1. Er zijn geen sensoren aangemaakt:
   1. Gebruiker opent configuratiepaneel.
   2. Systeem toont melding: "Geen sensoren ingesteld."

### Aanmaken sensoren

**Level:** Configuratietoegang

**Primary actor:** Technische dienst, installateur

**Stakeholders and interests:** 



**Preconditions:**

Het systeem is aan en volledig opgestart.

**Success guarantee:**

Aangemaakte sensoren met hun ingevulde parameters worden opgenomen in de lijst van sensoren.

**Main success scenario:**

1. Gebruiker opent configuratiepaneel.
2. Gebruiker klikt op "Voeg sensor toe".
3. Systeem geeft invoermogelijkheid weer.
4. Gebruiker vult relevante data in. (Tenminste naam, IP-adres en datatype)
5. Gebruiker klikt op "Toevoegen".
6. Systeem voegt gespecificeerde sensor toe aan de lijst.

**Extensions:** 

1. Er ontbreekt data (naam, IP-adres of datatype):
   1. Stappen 1-4 worden uitgevoerd.
   2. Gebruiker vult een of meerdere relevante datavelden niet in.
   3. Gebruiker klikt op "Toevoegen".
   4. Systeem geeft foutmelding "Ontbrekende data" met een rood kader om de betreffende velden.

### Aanpassen sensoren

**Level:** Configuratietoegang



**Primary actor: **Technische dienst, installateur



**Stakeholders and interests:** 



**Preconditions:**

Het systeem is aan, volledig opgestart en er bestaat tenminste 1 sensor.

**Success guarantee:**

De gebruiker kan de gegevensvelden van een sensor uit de lijst aanpassen.

**Main success scenario:**

1. Gebruiker opent configuratiepaneel.
2. Systeem toont lijst met sensoren.
3. Gebruiker selecteert sensor.
4. Gebruiker klikt op "Aanpassen".
5. Systeem toont gegevensveld van betreffende sensor.
6. Gebruiker past gegevens aan.
7. Gebruiker klikt op "Opslaan".
8. Systeem werkt lijst van sensoren bij.

**Extensions:**

1. Er ontbreekt data (naam, IP-adres of datatype):
   1. Stappen 1-4 worden uitgevoerd.
   2. Gebruiker vult een of meerdere relevante datavelden niet in.
   3. Gebruiker klikt op "Toevoegen".
   4. Systeem geeft foutmelding "Ontbrekende data" met een rood kader om de betreffende velden.

### Verwijderen sensoren

**Level:** Configuratietoegang



**Primary actor:** Technische dienst, installateur



**Stakeholders and interests:** 



**Preconditions:**

Het systeem is aan, volledig opgestart en er bestaat tenminste 1 sensor.

**Success guarantee:**

De gebruiker kan een sensor verwijderen uit de lijst.

**Main success scenario:**

1. Gebruiker opent configuratiepaneel.
2. Systeem toont lijst met sensoren.
3. Gebruiker selecteert sensor.
4. Gebruiker klikt op "Verwijderen".
5. Systeem toont dialoog "Weet u het zeker?".
6. Gebruiker klikt op "Ja".
7. Systeem werkt lijst met sensoren bij.

**Extensions:**

1. De gebruiker klikt per abuis op "Verwijderen".
   1. Succes scenario stappen 1-5 worden uitgevoerd.
   2. Gebruiker klikt op "Nee".
   3. Systeem werkt lijst met sensoren *niet* bij.
2. De gebruiker wil meerdere sensoren tegelijk verwijderen.
   1. Succes scenario stappen 1 en 2 worden uitgevoerd.
   2. Gebruiker selecteert verschillende sensoren.
   3. Gebruiker klikt op "Verwijderen".
   4. Succes scenario stappen 5 t/m 7 worden uitgevoerd.

### Inzien meetwaarden (realtime: laatst uitgelezen waarde)

**Level:** Informatietoegang



**Primary actor:** Productiemanager, technische dienst



**Stakeholders and interests:**



**Preconditions:**



**Success guarantee:**



**Main success scenario:**



**Extensions:**

### Inzien meetwaarden-historie

**Level:** Informatietoegang



**Primary actor:** Productiemanager, technische dienst



**Stakeholders and interests:**



**Preconditions:**



**Success guarantee:**



**Main success scenario:**



**Extensions:**

### Inzien analysewaarschuwingen

**Level:** Informatietoegang



**Primary actor: **Productiemanager, technische dienst



**Stakeholders and interests:**



**Preconditions:**



**Success guarantee:**



**Main success scenario:**



**Extensions:**

### Aanleveren analysewaarschuwingen

**Level:** IIOT-integratie



**Primary actor:** Analyseplatform



**Stakeholders and interests:**



**Preconditions:**



**Success guarantee:**



**Main success scenario:**



**Extensions:**

### Instellen analyseplatform(NA ONDERZOEK DATABASE/PLATFORM)

**Level:** IIOT-integratie



**Primary actor: **Analyseplatform



**Stakeholders and interests:**



**Preconditions:**



**Success guarantee:**



**Main success scenario:**



**Extensions:** 



# Overige functionele requirements





# Niet-functionele requirements





# Bronnen

Larman, C. (z.d.). *Applying UML and Patterns: An Introduction to Object-oriented Analysis and Design and Iterative Development*. Pearson. https://www.craiglarman.com/wiki/downloads/applying_uml/larman-ch6-applying-evolutionary-use-cases.pdf