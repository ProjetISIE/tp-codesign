#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "sys/alt_irq.h"

#define LCDCONTROLLER_NAME "/dev/lcdController"

// Global state
volatile uint16_t pwm_duty[24];
volatile bool pwm_active[24];
volatile uint32_t current_oe = 0;
volatile uint32_t current_nlatch = 0xFFFFFF;

volatile uint8_t page = 0; // 0 = 1-12, 1 = 13-24
volatile uint8_t sel1 = 0; // 1 to 24 (0 = none)
volatile uint8_t sel2 = 0; // 1 to 24 (0 = none)
volatile bool excess_sw = false;

FILE* lcd_fp = NULL;

volatile uint32_t pending_keys = 0;
volatile bool debounce_active = false;

// Forward declarations
void update_ui();
void process_switches();

void update_lcd() {
    if (!lcd_fp) return;
    fprintf(lcd_fp, "%c[2J", 27); // Clear LCD
    if (excess_sw) {
        fprintf(lcd_fp, "Exces Selection\n");
    } else {
        fprintf(lcd_fp, "PWM Generator\nPret.");
    }
}

void init_hardware() {
    for (int i=0; i<24; i++) {
        pwm_duty[i] = 0;
        pwm_active[i] = false;
        IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMTON_BASE, 0);
        IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMNLATCH_BASE, current_nlatch & ~(1 << i));
        IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMNLATCH_BASE, current_nlatch);
    }
    IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMOE_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_DATA(PIOLED_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_DATA(PIOHEX_BASE, 0xFFFFFFFF); // All displays blank
}

void update_hardware_pwm(int index) {
    if (index == 0) return;
    int i = index - 1;
    
    // Mettre a jour l'activation
    if (pwm_active[i]) {
        current_oe |= (1 << i);
    } else {
        current_oe &= ~(1 << i);
    }
    IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMOE_BASE, current_oe);
    
    // Mettre a jour le rapport cyclique
    IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMTON_BASE, pwm_duty[i]);
    IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMNLATCH_BASE, current_nlatch & ~(1 << i));
    IOWR_ALTERA_AVALON_PIO_DATA(PIOPWMNLATCH_BASE, current_nlatch);
}

void update_ui() {
    // Mise a jour des LEDs
    uint32_t led_val = (page == 1) ? 1 : 0;
    int offset = (page == 1) ? 12 : 0;
    for (int i=0; i<12; i++) {
        if (pwm_active[offset + i]) {
            led_val |= (1 << (i + 1));
        }
    }
    IOWR_ALTERA_AVALON_PIO_DATA(PIOLED_BASE, led_val);

    // Mise a jour des Afficheurs 7-segments
    uint32_t hex_val = 0xFFFFFFFF; // Eteint par defaut (0xF envoye aux decodeurs HW)
    
    if (!excess_sw && sel1 > 0) {
        // HEX7-HEX6 : Indice 1ere PWM
        uint8_t d1 = sel1 / 10;
        uint8_t d0 = sel1 % 10;
        hex_val &= ~0xFF000000;
        hex_val |= (d1 << 28) | (d0 << 24);
        
        // HEX3-HEX0 : Rapport cyclique
        uint16_t duty = pwm_duty[sel1 - 1];
        uint8_t dd3 = (duty / 1000) % 10;
        uint8_t dd2 = (duty / 100) % 10;
        uint8_t dd1 = (duty / 10) % 10;
        uint8_t dd0 = duty % 10;
        
        hex_val &= ~0x0000FFFF;
        if (duty < 1000) hex_val |= (0xF << 12); else hex_val |= (dd3 << 12);
        if (duty < 100)  hex_val |= (0xF << 8);  else hex_val |= (dd2 << 8);
        if (duty < 10)   hex_val |= (0xF << 4);  else hex_val |= (dd1 << 4);
        hex_val |= dd0;
        
        // HEX5-HEX4 : Indice 2eme PWM
        if (sel2 > 0) {
            uint8_t d3 = sel2 / 10;
            uint8_t d2 = sel2 % 10;
            hex_val &= ~0x00FF0000;
            hex_val |= (d3 << 20) | (d2 << 16);
        }
    }
    IOWR_ALTERA_AVALON_PIO_DATA(PIOHEX_BASE, hex_val);
}

void process_keys(uint32_t keys) {
    if (excess_sw || sel1 == 0) return;
    
    int s1_idx = sel1 - 1;
    
    // KEY3 : Activation / Desactivation
    if (keys & (1 << 3)) {
        bool new_state = !pwm_active[s1_idx];
        pwm_active[s1_idx] = new_state;
        update_hardware_pwm(sel1);
        if (sel2 > 0) {
            pwm_active[sel2 - 1] = new_state;
            update_hardware_pwm(sel2);
        }
    }
    
    // KEY1, KEY2, KEY0 : Rapport cyclique
    int delta = 0;
    if (keys & (1 << 1)) delta = 1;
    if (keys & (1 << 2)) delta = -1;
    if (keys & (1 << 0)) delta = 50;
    
    if (delta != 0) {
        int new_duty = (int)pwm_duty[s1_idx] + delta;
        if (new_duty > 1023) new_duty = 1023;
        if (new_duty < 0) new_duty = 0;
        
        pwm_duty[s1_idx] = new_duty;
        update_hardware_pwm(sel1);
        if (sel2 > 0) {
            pwm_duty[sel2 - 1] = new_duty;
            update_hardware_pwm(sel2);
        }
    }
    update_ui();
}

void process_switches() {
    uint32_t sw = IORD_ALTERA_AVALON_PIO_DATA(PIOSW_BASE);
    page = (sw & 1) ? 1 : 0;
    
    int active_count = 0;
    int first_sel = 0;
    int second_sel = 0;
    int offset = (page == 1) ? 12 : 0;
    
    for (int i=1; i<=12; i++) {
        if (sw & (1 << i)) {
            active_count++;
            if (active_count == 1) first_sel = i + offset;
            else if (active_count == 2) second_sel = i + offset;
        }
    }
    
    if (active_count > 2) {
        if (!excess_sw) {
            excess_sw = true;
            update_lcd();
        }
    } else {
        if (excess_sw) {
            excess_sw = false;
            update_lcd();
        }
        sel1 = first_sel;
        sel2 = second_sel;
    }
    update_ui();
}

// ISR Timer pour l'Anti-rebond asynchrone
static void timer_isr(void* context) {
    // Acquitter l'interruption du timer
    IOWR_ALTERA_AVALON_TIMER_STATUS(HIGHRESTIMER_BASE, 0);
    IOWR_ALTERA_AVALON_TIMER_CONTROL(HIGHRESTIMER_BASE, 0); // Stop
    
    process_switches();
    
    if (pending_keys) {
        process_keys(pending_keys);
        pending_keys = 0;
    }
    
    // Nettoyer toute activite parasite intervenue pendant le debounce
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOSW_BASE, 0xFFFFFFFF);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOKEY_BASE, 0xF);
    
    debounce_active = false;
    
    // Reactiver les IRQ PIO
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOSW_BASE, 0x1FFF);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOKEY_BASE, 0xF);
}

static void pio_sw_isr(void* context) {
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOSW_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOKEY_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOSW_BASE, 0xFFFFFFFF);
    
    if (!debounce_active) {
        debounce_active = true;
        // Lancer le timer pour ~30ms (clock 100MHz = 3 000 000 ticks)
        IOWR_ALTERA_AVALON_TIMER_PERIODL(HIGHRESTIMER_BASE, (3000000 & 0xFFFF));
        IOWR_ALTERA_AVALON_TIMER_PERIODH(HIGHRESTIMER_BASE, (3000000 >> 16));
        IOWR_ALTERA_AVALON_TIMER_CONTROL(HIGHRESTIMER_BASE, ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
    }
}

static void pio_key_isr(void* context) {
    pending_keys |= IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIOKEY_BASE);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOSW_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOKEY_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIOKEY_BASE, 0xF);
    
    if (!debounce_active) {
        debounce_active = true;
        IOWR_ALTERA_AVALON_TIMER_PERIODL(HIGHRESTIMER_BASE, (3000000 & 0xFFFF));
        IOWR_ALTERA_AVALON_TIMER_PERIODH(HIGHRESTIMER_BASE, (3000000 >> 16));
        IOWR_ALTERA_AVALON_TIMER_CONTROL(HIGHRESTIMER_BASE, ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
    }
}

int main() {
    lcd_fp = fopen(LCDCONTROLLER_NAME, "w");
    update_lcd();
    init_hardware();
    process_switches();
    
    // Enregistrement des Interruptions
    alt_ic_isr_register(HIGHRESTIMER_IRQ_INTERRUPT_CONTROLLER_ID, HIGHRESTIMER_IRQ, timer_isr, NULL, 0);
    alt_ic_isr_register(PIOSW_IRQ_INTERRUPT_CONTROLLER_ID, PIOSW_IRQ, pio_sw_isr, NULL, 0);
    alt_ic_isr_register(PIOKEY_IRQ_INTERRUPT_CONTROLLER_ID, PIOKEY_IRQ, pio_key_isr, NULL, 0);
    
    // Activation initiale des masques PIO
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOSW_BASE, 0x1FFF); // 13 switches
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIOKEY_BASE, 0xF);   // 4 keys
    
    while(1) {
        // Aucune attente active ! Le CPU dort virtuellement ici.
    }
    
    return 0;
}
