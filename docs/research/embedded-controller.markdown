# Onderzoek Embedded Controller

## Inleiding

In dit onderzoeksdocument stel ik vast welke embedded controller er gebruikt wordt voor het project. De [projectopdracht](../process/PvA.markdown#4-doelstelling-opdracht-en-op-te-leveren-resultaten-voor-het-bedrijf) staat beschreven in het PvA. Onder embedded controller vallen eigenlijk allerlei soorten microcontrollers, maar ook embedded en industriële PC's. De hoofdvraag luidt dus:

**Welke embedded controller past het beste bij dit project?** (Multi-criteria decision making)

Met de deelvragen:

1. Wat zijn de performance-eisen aan de embedded controller? (Literature Study, Lab)
2. Wat zijn de gebruikerseisen aan de embedded controller? (Explore User Requirements)
3. Wat zijn de fysieke eisen aan de embedded controller? (Explore User Requirements)
4. Welke embedded controllers zijn er beschikbaar? (Available Product Analysis)

Deze vragen worden beantwoord door middel van de ICT-Research Methods, waarvan de methode tussen de haakjes achter de (deel)vraag staat.

## Deelvraag 1: Wat zijn de performance-eisen aan het systeem?

### CPU en RAM

Uit het database-onderzoek blijkt dat op mijn laptop (Ryzen 5 3500U met 4 cores) de database voldoende snel draait. Wanneer ik de beschreven test draai, dus met bijna 22.000 writes per seconde neemt de database volgens *top* ~47% van een enkele CPU-core in beslag en slechts 0.6% RAM:

![](embedded-controller/top-db.png)

Daarbij komt het wegschrijven met Python en het draaien van de rest van het besturingssysteem, dit zorgt volgens de *gnome-system-monitor* voor ongeveer 20-25% belasting over alle cores:

![](embedded-controller/gnome-sysmon-db.png)

Naast het draaien van de database moet er ook ruimte zijn voor een gebruikersinterface en de onderscheppingssoftware, dat samen een softwarepakket wordt. Voor de gebruikersinterface heb ik geen test, maar ik kan als stand-in voor de onderscheppingssoftware de testsoftware(*profinet_sniffer*) uit het Profinet-onderzoek pakken. In plaats van *top* gebruik ik hier *htop* zodat ik kan filteren op mijn *profinet_sniffer*. Wanneer ik deze draai en er met *tcpreplay* netwerkverkeer heen stuur dan gebruikt dit 90% van een enkele CPU:

![](embedded-controller/htop-sniffer.png)

Over de gebruikersinterface en daarbij het ophalen van de data kan voorlopig alleen een educated guess gedaan worden. Het gebruiken van de interface zorgt voor een variabele belasting op het systeem, hoeveel data er opgehaald wordt is namelijk aan de gebruiker. Deze bepaalt indirect hoeveel data er uit de database nodig is door bijvoorbeeld een visualisatie van een groot tijdsbestek te kiezen of slechts van een paar seconden. 

Alle bovenstaande factoren maken het aannemelijk dat een systeem met ongeveer dezelfde processorkracht als mijn laptop (moderne X86 dual-core CPU met hyper-threading en 8GB RAM) ruim voldoende is om het hele systeem op te draaien. Uit geen van de tests bleek RAM een probleem te zijn.

### Opslag

De opslag van het systeem wordt relatief snel gevuld, blijkt uit het database-onderzoek. De logging-precisie is hierbij belangrijk. Uit een gesprek met de stakeholder bleek dat 10Hz(#todo ff navragen) voldoende was. In de test heb ik de maximale snelheid aangehouden die de IO-Link masters konden leveren, 200Hz. Dit leverde echter bijna 160GB per 24 uur op. Binnen 7 dagen is dat een terabyte. 

Op de gevraagde 10Hz levert het systeem slechts 8GB per dag op. Dit is beter haalbaar, op een terabyte kan nu iets meer dan 100 dagen gelogd worden. In het onderzoek is een groter datatype (64 bit double) gekozen voor de sensorwaarde dan die daadwerkelijk voorkomt in de Soda Factory. 

## Deelvraag 2: Wat zijn de gebruikerseisen aan de embedded controller?

Voor deze deelvraag heb ik een aantal interviewvragen gesteld aan de stakeholder, deze zijn beantwoord en de antwoorden staan **dikgedrukt** achter de vraag:

- Hoeveel opslag/ hoelang moet er gelogd worden? Op 10Hz verwacht ik met 1TB opslag ongeveer 100 dagen te kunnen loggen voor de Soda Factory, dit blijkt uit onderzoek. **10Hz is meer dan genoeg en ook 100 dagen is meer dan zat. Ik denk dat als we een logging history van 30 dagen kunnen houden, dat er tijd genoeg is om analyzes te kunnen doen op de data. Dus 1TB is al plenty. 512 zou ook nog uitkunnen. Zeker als we in de software selectief zouden kunnen zijn in de frequentie van logging per signaal.**
- Hoe willen we het systeem benaderen qua interface? Gebruiken we een scherm en toetsenbord/muis (maakt het wat minder goed mogelijk om eenvoudig in te bouwen), gebruiken we een Remote Desktop Protocol (dit maakt inbouw eenvoudiger, kan een headless kastje zijn) of misschien een web interface. **RDP is helemaal OK. Ook het meest praktische.** 
- Wat is het budget voor de embedded controller? (De gehele ontwikkeling kan gewoon plaatsvinden op mijn laptop, maar het is wel leuk om een beetje een idee te hebben waar de stakeholder aan denkt.) **Als ik naar de Lenovo M-series of Asus NUC kijk denk ik dat we voor onder 1000 euro wat moeten kunnen regelen. Naast de PC zullen we ook nog een extra SSD van 512 of 1TB moeten plaatsen. Voor je budget in het verslag mag je daar wel rekening mee houden.**

## Deelvraag 3: Wat zijn de fysieke eisen aan de embedded controller?

Hetzelfde als bij de vorige deelvraag zijn hier een aantal vragen gesteld:

- Moet het geheel kunnen monteren op de DIN-rail in de regelkast? (Dit maakt het geheel flink duurder, heb ik gezien) **Hoeft niet per se op DIN, is wel mooi (als de ruimte er daarvoor nog zou zijn. Voor de Lenovo ThinkCentre serie zijn wel brackets te verkrijgen. Google search op 'lenovo thinkcentre mounting bracket' voor montage in het besturingspaneel. Montageplaat, zijwand of zelfs onder de 'dubbele bodem'.**
- Moet de controller op alleen 24V werken of kan het ook gewoon op 230V? **Mag beide. 24VDC zal het meteen erg duur van worden. 230VAC is prima**
- Moet de netwerkswitch inbegrepen zijn of kunnen we simpelweg de eis stellen dat er een managed netwerkswitch in het de regelkast aanwezig is? **Dat laatste is OK.**



## Deelvraag 4: Welke embedded controllers zijn beschikbaar?

Uit antwoorden op de vorige deelvragen blijkt dat een *small form factor* consumenten-PC zoals een Lenovo ThinkCentre of Asus NUC voldoende is voor het project. 

Hierbij is de Lenovo ThinkCentre M75q het meest geschikt omdat die in principe compleet te koop is. Wanneer ik met de Lenovo configurator een AMD-variant configureer die aan de eisen voldoet dan krijg ik het volgende voor 462 euro:

| Onderdeel: | Type:                                   |
| ---------- | --------------------------------------- |
| Processor  | AMD Ryzen™ 5 PRO 5655GE, 6C/12T, 3.4GHz |
| RAM        | 8 GB DDR4-3200MHz                       |
| Opslag     | 1TB SSD M.2 2280 PCIe Gen4              |

Deze ThinkCentre is meer dan sterk genoeg om de software te draaien en vanwege de ingebouwde videokaart is het mogelijk om deze headless te gebruiken. Verder voldoet hij ook aan alle stakeholder-eisen. Ik heb hem zonder OS geconfigureerd omdat er een specifieke Linux-distro op moet komen met de vereiste software.

Op de grote elektrowebsites zoals Mouser en RS-Components zijn ook industriële PC's beschikbaar. Deze zijn behoorlijk duur omdat industriële PC's veel steviger uitgevoerd zijn dan standaard consumenten PC's. Deze industriele PC's beginnen bij ongeveer 350 euro, maar deze hebben een Intel Atom van een oudere generatie of een ARM-processor. Deze zijn vaak single- of dual-core met een lage kloksnelheid en voldoen niet aan de performance-eis, of in het geval van ARM moet ervoor ge-crosscompiled worden wat de softwareontwikkeling bemoeilijkt.

Industriële PC's beschikken over het algemeen over oudere hardware. Dit is bewust; sommige processoren hebben extra ondersteuning voor embedded toepassingen, en worden daarom langer en rigoureuzer ondersteund en geproduceerd (ElecD3sDSL, 2024). 



## Resultaten

De eisen aan de embedded controller zijn als volgt:

| Categorie   | Nummer | Naam              | Beschrijving                                                 |
| ----------- | ------ | ----------------- | ------------------------------------------------------------ |
| Performance | P-1    | Processor         | De processor van de embedded controller moet tenminste over 2 processorcores en 4 threads beschikken. |
|             | P-2    | RAM               | De embedded controller moet tenminste over 8GB RAM beschikken. |
| Gebruiker   | G-1    | Opslag            | De embedded controller moet tenminste over 512GB opslag beschikken. |
|             | G-2    | Fysieke interface | Het systeem wordt benaderd via een Remote Desktop Protocol.  |
| Budget      | B-1    | Budget            | Het budget voor het systeem is 1000 euro.                    |
| Fysiek      | F-1    | Montage           | Het systeem moet ergens in de regelkast gemonteerd worden met een beugel. Waar precies is niet vastgesteld. |
|             | F-2    | Voeding           | 230VAC of 24VDC                                              |
|             | F-3    | Switch            | De managed switch wordt niet inbegrepen in het te leveren systeem; er wordt verwacht dat deze aanwezig is in de regelkast van de stakeholder. |





## Conclusie

De Lenovo ThinkCentre M75q is de uiteindelijke keuze voor gebruik als embedded controller. Deze PC is op hardware-performance niveau voldoende snel en biedt verder de juiste fysieke kenmerken om in het project gebruikt te worden. Omdat het systeem een consumentenproduct is en geen industriële PC is het een stuk goedkoper, en valt dus met gemak onder de budget-eis van 1000 euro. Verder worden er verschillende montage-opties aangeboden voor deze PC waardoor deze goed in de regelkast gebouwd kan worden.



## Bronvermelding

ElecD3sDSL. (2024, 22 oktober). *Fit and forget – Why do industrial solutions not use the latest technology?* DSL Industrial Computing. https://www.dsl-industrialcomputing.co.uk/industrial-solutions-dont-use-latest-technology/