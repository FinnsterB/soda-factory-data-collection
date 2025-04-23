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

### Procesoperator of procestechnoloog



### Medewerker storingsdienst



### Medewerker inkoop



## Omgeving



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

Uiteindelijk is het de bedoeling dat ons systeem toevoegingen maakt aan het onderhoud van de productielijn en wellicht grond biedt voor optimalisaties. 





# Usecase-beschrijvingen





# Overige functionele requirements





# Niet-functionele requirements





# Bronnen