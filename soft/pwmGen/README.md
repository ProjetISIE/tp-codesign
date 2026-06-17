# Générateur PWM pour kit TerASIC DE2-115

Le système est configuré initiallement avec:

- Un Softcore NIOS II-e (gen 2) 
- Un contrôleur SDRAM exploitant les 64ko de SDRAM embarqués sur DE2-115 
- Une PLL générant deux signaux 100MHz, un pour processeur, un pour SDRAM
- Deux timers (1ms et 1µs) 
- Un JTAG UART

## Objectif

Piloter 24 canaux PWM, tous cadencés à 1kHz, mais ayant chacun un état
d’activation et un rapport cyclique (sur 10bits, 0 à 1023) indépendant.

Les 24 canaux PWM sont directement associés aux 24 premières lignes GPIO:
PWM0 sur GPIO[0], PWM1 sur GPIO[1]…

Le signal d’horloge des PMW (1kHz) sort sur la GPIO[35] pour les tests.

Surtout pas d’attente active, bloquage, polling; uniquement des interruptions.

## Interface Utilisateur

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

## Configuration Materielle Additionnelle

Pour repondre aux contraintes temporelles du systeme (particulierement
l'impossibilite de gerer une interruption de 1us sur le Nios II/e pour 24 PWM),
l'architecture Qsys suivante doit etre ajoutee. Cette approche utilise le module
`modMultiPWM.v` fourni pour decharger le processeur.

- Peripheriques d'E/S (PIOs) dans Qsys:
  - `pioSW`: 13 bits en entree (SW0-SW12), interruptions "Any Edge"
  - `pioKEY` : 4 bits en entree (KEY0-KEY3), interruptions "Falling Edge"
  - `pioLED` : 13 bits en sortie (LED0-LED12)
  - `pioHEX` : 32 bits en sortie pour le multiplexage des afficheurs HEX
  - **Altera Character LCD** pour piloter l'ecran 16x2
  - `pio_pwm_ton` : 10 bits en sortie (bus `Ton` vers le `modMultiPWM`)
  - `pio_pwm_nlatch` : 24 bits en sortie (bus `nLatch` vers le `modMultiPWM`,
  	 actif a l'etat bas, defaut `0xFFFFFF`)
  - `pio_pwm_oe` : 24 bits en sortie (bus `oe` vers le `modMultiPWM`, defaut
  	`0x000000`)

- Integration Top-Level Verilog :
  - Instanciation du systeme Qsys
  - Instanciation du module `modMultiPWM` (`NB_PWM=24`, `RESOLUTION=10`)
  - Connexion des bus `Ton`, `nLatch` et `oe` du `modMultiPWM` aux PIOs
  	correspondants exportes de Qsys
  - Generation d'une horloge `clk_1MHz` (1.024MHz) a partir de l'horloge 100MHz
  	via un diviseur, connectee aux entrees `ClkIn` et utilisee pour generer le
  	signal test 1kHz sur `GPIO[35]`
  - Connexion du bus `PWMout` sur `GPIO[0..23]`.