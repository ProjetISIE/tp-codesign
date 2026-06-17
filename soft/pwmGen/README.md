# Générateur PWM pour kit TerASIC DE2-115

Le système est configuré initiallement avec:

- Un Softcore NIOS II-e (gen 2) 
- Un contrôleur SDRAM exploitant les 64ko de SDRAM embarqués sur DE2-115 
- Une PLL générant deux signaux 100MHz, un pour processeur, un pour SDRAM
- Deux timers (1ms et 1µs) 
- Un JTAG UART

Pilote 24 canaux PWM, tous cadencés à 1kHz, mais ayant chacun un état
d’activation et un rapport cyclique (sur 10bits, 0 à 1023) indépendant.

Les 24 canaux PWM sont directement associés aux 24 premières lignes GPIO:
PWM0 sur GPIO[0], PWM1 sur GPIO[1]…

Le signal d’horloge des PMW (1kHz) sort sur la GPIO[35] pour les tests.

Les LED1 à LED12 représentent l’état d’activation des PWM, en deux pages
navigables avec le SW0, tandis que la LED0 indique la page actuelle
(allumée : page haute 13-24, éteinte : page basse 1-12).

Les SW1 à 12 sélectionnent les une ou deux PWM correspondantes à configurer
en activation et rapport cyclique. La configuration se fait à partir de la
celle de la première sélectionnée (si la première est allumée et la seconde éteinte
et que l’on presse KEY3, les deux s’éteignent; idem pour le point de départ
d’incrément/décrément du rapport cyclique). Si plus de deux switches sont activés,
l’écran LCD affiche "Excès Sélection" et aucune configuration ne change.

L’indice (1 à 24) de la première PWM sélectionnée s’affiche sur les afficheurs sept
segments HEX7-HEX6, l’indice de la seconde PWM sélectionnée s’affiche sur HEX5-HEX4.
Les afficheurs sept segments s’éteignent en l’absence de sélection.

Le rapport cyclique en cours de configuration s’affiche sur HEX3-HEX0 (0 à 1023).

L’état d’activation des PWM sélectionnées se bascule avec KEY3,
métant directement à jour la LED correspondante.

Le rapport cyclique se configure avec KEY1 pour incrémenter, KEY2 pour décrémenter,
et le KEY0 pour incrémenter rapidement (+50).