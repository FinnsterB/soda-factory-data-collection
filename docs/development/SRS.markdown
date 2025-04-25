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

## Actors

De actors die van dit systeem gebruik gaan maken zijn de volgende:

### Productiemanager

De productiemanager houdt zich bezig met de optimalisatie van de productielijn en verlangt een bepaald soort gegevens.

### Technische dienst

De technische dienst houdt zich bezig met het onderhoud van de productielijn en verlangt een bepaald soort gegevens.

### Installateur



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

Het systeem biedt informatie aan de *inkoopmedewerker*, *procesoperator* en de *onderhoudsdienst*. Deze actors moeten allemaal kunnen zien of de productielijn nog goed draait, of er waarschuwingen zijn en in het geval van calamiteiten wellicht terugkijken naar historische gegevens. 

De instelmogelijkheid van het systeem hoeft niet bereikbaar te zijn voor de *inkoopmedewerker*. Het is daarentegen wel nodig dat de *installateur*, dit wel kan. Zo kan de *installateur* een werkend systeem opleveren. Tevens kan de *installateur* ook bij de installatie van het systeem het analyseplatform instellen. Het analyseplatform wordt hoogstwaarschijnlijk een bestaand IIOT-platform waarvoor enige authenticatie en andere instelmogelijkheden zijn. 



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





# Overige functionele requirements





# Niet-functionele requirements





# Bronnen