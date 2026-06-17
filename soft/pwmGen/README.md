# Générateur PWM pour kit TerASIC DE2-115

Le FPGA est configuré initiallement avec:

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