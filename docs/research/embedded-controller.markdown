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

Alle bovenstaande factoren maken het aannemelijk dat een systeem met ongeveer dezelfde processorkracht als mijn laptop (moderne X86 quad-core CPU met hyper-threading en 8GB RAM) voldoende is om het hele systeem op te draaien. Uit geen van de tests bleek RAM een probleem te zijn.

### Opslag

De opslag van het systeem wordt relatief snel gevuld, blijkt uit het database-onderzoek. De logging-precisie is hierbij belangrijk. Uit een gesprek met de stakeholder bleek dat 10Hz(#todo ff navragen) voldoende was. In de test heb ik de maximale snelheid aangehouden die de IO-Link masters konden leveren, 200Hz. Dit leverde echter bijna 160GB per 24 uur op. Binnen 7 dagen is dat een terabyte. 

Op de gevraagde 10Hz levert het systeem slechts 8GB per dag op. Dit is beter haalbaar, op een terabyte kan nu iets meer dan 100 dagen gelogd worden. In het onderzoek is een groter datatype (64 bit double) gekozen voor de sensorwaarde dan die daadwerkelijk voorkomt in de Soda Factory. 

## Deelvraag 2: Wat zijn de gebruikerseisen aan de embedded controller?

#todo interview

Scherm er direct aan, webinterface of een remote connection zoals VNC of xrdp.

## Deelvraag 3: Wat zijn de fysieke eisen aan de embedded controller?





## Deelvraag 4: Welke embedded controllers zijn beschikbaar?

Op de grote elektrawebsites zoals Mouser en RS-Components zijn industriele PC's beschikbaar. Deze zijn behoorlijk duur omdat industriele PC's veel steviger uitgevoerd zijn en een groter temperatuurbereik hebben. Deze PC's beginnen bij 1000 euro, met een Intel Atom CPU. In deelvraag 1 is vastgesteld dat de PC tenminste een quad-core CPU met hyper-threading moet hebben, en de Atom heeft dat niet. Pas de modernere (van de afgelopen 5 jaar) Intel i3, i5 en i7 processoren beschikken hierover. Industriele PC die daarmee uitgerust zijn, kosten 2000+ Euro. 

## Resultaten





## Conclusie