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

#todo interview

Scherm er direct aan, webinterface of een remote connection zoals VNC of xrdp.

## Deelvraag 3: Wat zijn de fysieke eisen aan de embedded controller?





## Deelvraag 4: Welke embedded controllers zijn beschikbaar?

Op de grote elektrawebsites zoals Mouser en RS-Components zijn industriele PC's beschikbaar. Deze zijn behoorlijk duur omdat industriele PC's veel steviger uitgevoerd zijn dan standaard consumenten PC's. Deze industriele PC's beginnen bij ongeveer 350 euro, maar deze hebben een Intel Atom van een oudere generatie. Deze zijn vaak single- of dual-core met een lage kloksnelheid en voldoen niet aan de performance-eis. 

Industriele PC's beschikken vaak over oudere hardware, ze gebruiken voornamelijk processoren van een aantal generaties oud. Dit is bewust; sommige processoren hebben extra ondersteuning voor embedded toepassingen, en worden daarom langer en rigoureuzer ondersteund en geproduceerd (ElecD3sDSL, 2024). Ook zijn na een aantal jaar de meeste bugs en fouten uit de drivers opgelost, waardoor de softwareondersteuning robuuster is.

Gelukkig zijn er modernere Intel Atom's die beschikken over 4 cores en 4 threads. Deze processoren voldoen aan de performance-eis van het systeem. Deze zijn te vinden in industriele PC's vanaf ongeveer 700 euro. Wanneer ik op de sites van elektraleveranciers kijk dan komt daar de volgende lijst uit:

| Naam                     | Fabrikant       | Leverancier | Processor                   | Voeding  | Montage               | Prijs                                       | Link                                                         |
| ------------------------ | --------------- | ----------- | --------------------------- | -------- | --------------------- | ------------------------------------------- | ------------------------------------------------------------ |
| UP Squared Pro 7000 Edge | UP Systems      | Mouser      | Atom x7425E 4C/4T           | 12VDC 6A | Geen/Alleen dev board | 465,60                                      | [Mouser](https://nl.mouser.com/ProductDetail/IEI/TANK-600-CV-N2600-8C-2G-R11?qs=sGAEpiMZZMv0DJfhVcWlK6FmZcYeBHRRZjNuoeJc7hhPcUKxGCxaiA%3D%3D) |
| AMOS-3007                | VIA             | Mouser      | Atom x64xx 4C/4T            | 9-36VDC  | VESA/Wall mountable   | 710,60                                      | [Mouser](https://nl.mouser.com/ProductDetail/VIA/AMOS-3007-1Q15A0?qs=sGAEpiMZZMv0DJfhVcWlK9Igd9QWlgUBiExwCzqIKSJJVS1iDs1kMQ%3D%3D) |
| UPC 2430                 | Phoenix Contact | Mouser      | Atom x6413E 4C/4T           | 24VDC    | DIN                   | 873,21                                      | [Mouser](https://nl.mouser.com/ProductDetail/Phoenix-Contact/1433152?qs=2SLPxufLcgDWNiE2lJTk9A%3D%3D) |
| Siemens Simatic          | Siemens         | RS-online   | Atom x6413E 4C/4T (4GB RAM) | 24VDC    | Wall mountable        | 861,30                                      | [RS-Online](https://nl.rs-online.com/web/p/industrial-computers/2713544) |
| Helix 310                | ONLOGIC         | ONLOGIC     | Intel Pentium J6425(4C/4T)  | 24DC     | DIN                   | 710,27 (incl DIN mount, 24V Terminal block) | [ONLOGIC](https://www.onlogic.com/nl/store/hx310/#specifications) |

Alle bovenstaande industriele PC's beschikken over de mogelijkheid om de opslag uit te breiden. Dit kan gedaan worden naar de eisen van de stakeholder.

De Soda Factory beschikt zelf over een B&R Automation PC 910. Deze heeft een Intel Core i7.  

## Resultaten





## Conclusie





## Bronvermelding

ElecD3sDSL. (2024, 22 oktober). *Fit and forget – Why do industrial solutions not use the latest technology?* DSL Industrial Computing. https://www.dsl-industrialcomputing.co.uk/industrial-solutions-dont-use-latest-technology/