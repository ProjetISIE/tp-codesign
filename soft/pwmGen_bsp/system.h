/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'mainCpu' in SOPC Builder design 'pwmGen'
 * SOPC Builder design path: ../../pwmGen.sopcinfo
 *
 * Generated: Wed Jun 17 18:14:42 CEST 2026
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x08000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "mainCpu"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x08000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_LCD_16207
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTPLL


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtagUart"
#define ALT_STDERR_BASE 0x80010d8
#define ALT_STDERR_DEV jtagUart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtagUart"
#define ALT_STDIN_BASE 0x80010d8
#define ALT_STDIN_DEV jtagUart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtagUart"
#define ALT_STDOUT_BASE 0x80010d8
#define ALT_STDOUT_DEV jtagUart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "pwmGen"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYSTEMTIMER
#define ALT_TIMESTAMP_CLK HIGHRESTIMER


/*
 * highResTimer configuration
 *
 */

#define ALT_MODULE_CLASS_highResTimer altera_avalon_timer
#define HIGHRESTIMER_ALWAYS_RUN 0
#define HIGHRESTIMER_BASE 0x8001000
#define HIGHRESTIMER_COUNTER_SIZE 32
#define HIGHRESTIMER_FIXED_PERIOD 0
#define HIGHRESTIMER_FREQ 100000000
#define HIGHRESTIMER_IRQ 2
#define HIGHRESTIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define HIGHRESTIMER_LOAD_VALUE 99
#define HIGHRESTIMER_MULT 1.0E-6
#define HIGHRESTIMER_NAME "/dev/highResTimer"
#define HIGHRESTIMER_PERIOD 1
#define HIGHRESTIMER_PERIOD_UNITS "us"
#define HIGHRESTIMER_RESET_OUTPUT 0
#define HIGHRESTIMER_SNAPSHOT 1
#define HIGHRESTIMER_SPAN 32
#define HIGHRESTIMER_TICKS_PER_SEC 1000000
#define HIGHRESTIMER_TIMEOUT_PULSE_OUTPUT 0
#define HIGHRESTIMER_TYPE "altera_avalon_timer"


/*
 * jtagUart configuration
 *
 */

#define ALT_MODULE_CLASS_jtagUart altera_avalon_jtag_uart
#define JTAGUART_BASE 0x80010d8
#define JTAGUART_IRQ 0
#define JTAGUART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAGUART_NAME "/dev/jtagUart"
#define JTAGUART_READ_DEPTH 64
#define JTAGUART_READ_THRESHOLD 8
#define JTAGUART_SPAN 8
#define JTAGUART_TYPE "altera_avalon_jtag_uart"
#define JTAGUART_WRITE_DEPTH 64
#define JTAGUART_WRITE_THRESHOLD 8


/*
 * lcdController configuration
 *
 */

#define ALT_MODULE_CLASS_lcdController altera_avalon_lcd_16207
#define LCDCONTROLLER_BASE 0x80010c0
#define LCDCONTROLLER_IRQ -1
#define LCDCONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCDCONTROLLER_NAME "/dev/lcdController"
#define LCDCONTROLLER_SPAN 16
#define LCDCONTROLLER_TYPE "altera_avalon_lcd_16207"


/*
 * pioHEX configuration
 *
 */

#define ALT_MODULE_CLASS_pioHEX altera_avalon_pio
#define PIOHEX_BASE 0x8001070
#define PIOHEX_BIT_CLEARING_EDGE_REGISTER 0
#define PIOHEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOHEX_CAPTURE 0
#define PIOHEX_DATA_WIDTH 32
#define PIOHEX_DO_TEST_BENCH_WIRING 0
#define PIOHEX_DRIVEN_SIM_VALUE 0
#define PIOHEX_EDGE_TYPE "NONE"
#define PIOHEX_FREQ 100000000
#define PIOHEX_HAS_IN 0
#define PIOHEX_HAS_OUT 1
#define PIOHEX_HAS_TRI 0
#define PIOHEX_IRQ -1
#define PIOHEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIOHEX_IRQ_TYPE "NONE"
#define PIOHEX_NAME "/dev/pioHEX"
#define PIOHEX_RESET_VALUE 0
#define PIOHEX_SPAN 16
#define PIOHEX_TYPE "altera_avalon_pio"


/*
 * pioKEY configuration
 *
 */

#define ALT_MODULE_CLASS_pioKEY altera_avalon_pio
#define PIOKEY_BASE 0x8001090
#define PIOKEY_BIT_CLEARING_EDGE_REGISTER 0
#define PIOKEY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOKEY_CAPTURE 1
#define PIOKEY_DATA_WIDTH 4
#define PIOKEY_DO_TEST_BENCH_WIRING 0
#define PIOKEY_DRIVEN_SIM_VALUE 0
#define PIOKEY_EDGE_TYPE "FALLING"
#define PIOKEY_FREQ 100000000
#define PIOKEY_HAS_IN 1
#define PIOKEY_HAS_OUT 0
#define PIOKEY_HAS_TRI 0
#define PIOKEY_IRQ 4
#define PIOKEY_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIOKEY_IRQ_TYPE "LEVEL"
#define PIOKEY_NAME "/dev/pioKEY"
#define PIOKEY_RESET_VALUE 0
#define PIOKEY_SPAN 16
#define PIOKEY_TYPE "altera_avalon_pio"


/*
 * pioLED configuration
 *
 */

#define ALT_MODULE_CLASS_pioLED altera_avalon_pio
#define PIOLED_BASE 0x8001080
#define PIOLED_BIT_CLEARING_EDGE_REGISTER 0
#define PIOLED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOLED_CAPTURE 0
#define PIOLED_DATA_WIDTH 13
#define PIOLED_DO_TEST_BENCH_WIRING 0
#define PIOLED_DRIVEN_SIM_VALUE 0
#define PIOLED_EDGE_TYPE "NONE"
#define PIOLED_FREQ 100000000
#define PIOLED_HAS_IN 0
#define PIOLED_HAS_OUT 1
#define PIOLED_HAS_TRI 0
#define PIOLED_IRQ -1
#define PIOLED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIOLED_IRQ_TYPE "NONE"
#define PIOLED_NAME "/dev/pioLED"
#define PIOLED_RESET_VALUE 0
#define PIOLED_SPAN 16
#define PIOLED_TYPE "altera_avalon_pio"


/*
 * pioPwmNLatch configuration
 *
 */

#define ALT_MODULE_CLASS_pioPwmNLatch altera_avalon_pio
#define PIOPWMNLATCH_BASE 0x8001050
#define PIOPWMNLATCH_BIT_CLEARING_EDGE_REGISTER 0
#define PIOPWMNLATCH_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOPWMNLATCH_CAPTURE 0
#define PIOPWMNLATCH_DATA_WIDTH 24
#define PIOPWMNLATCH_DO_TEST_BENCH_WIRING 0
#define PIOPWMNLATCH_DRIVEN_SIM_VALUE 0
#define PIOPWMNLATCH_EDGE_TYPE "NONE"
#define PIOPWMNLATCH_FREQ 100000000
#define PIOPWMNLATCH_HAS_IN 0
#define PIOPWMNLATCH_HAS_OUT 1
#define PIOPWMNLATCH_HAS_TRI 0
#define PIOPWMNLATCH_IRQ -1
#define PIOPWMNLATCH_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIOPWMNLATCH_IRQ_TYPE "NONE"
#define PIOPWMNLATCH_NAME "/dev/pioPwmNLatch"
#define PIOPWMNLATCH_RESET_VALUE 16777215
#define PIOPWMNLATCH_SPAN 16
#define PIOPWMNLATCH_TYPE "altera_avalon_pio"


/*
 * pioPwmOe configuration
 *
 */

#define ALT_MODULE_CLASS_pioPwmOe altera_avalon_pio
#define PIOPWMOE_BASE 0x8001040
#define PIOPWMOE_BIT_CLEARING_EDGE_REGISTER 0
#define PIOPWMOE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOPWMOE_CAPTURE 0
#define PIOPWMOE_DATA_WIDTH 24
#define PIOPWMOE_DO_TEST_BENCH_WIRING 0
#define PIOPWMOE_DRIVEN_SIM_VALUE 0
#define PIOPWMOE_EDGE_TYPE "NONE"
#define PIOPWMOE_FREQ 100000000
#define PIOPWMOE_HAS_IN 0
#define PIOPWMOE_HAS_OUT 1
#define PIOPWMOE_HAS_TRI 0
#define PIOPWMOE_IRQ -1
#define PIOPWMOE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIOPWMOE_IRQ_TYPE "NONE"
#define PIOPWMOE_NAME "/dev/pioPwmOe"
#define PIOPWMOE_RESET_VALUE 0
#define PIOPWMOE_SPAN 16
#define PIOPWMOE_TYPE "altera_avalon_pio"


/*
 * pioPwmTon configuration
 *
 */

#define ALT_MODULE_CLASS_pioPwmTon altera_avalon_pio
#define PIOPWMTON_BASE 0x8001060
#define PIOPWMTON_BIT_CLEARING_EDGE_REGISTER 0
#define PIOPWMTON_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOPWMTON_CAPTURE 0
#define PIOPWMTON_DATA_WIDTH 10
#define PIOPWMTON_DO_TEST_BENCH_WIRING 0
#define PIOPWMTON_DRIVEN_SIM_VALUE 0
#define PIOPWMTON_EDGE_TYPE "NONE"
#define PIOPWMTON_FREQ 100000000
#define PIOPWMTON_HAS_IN 0
#define PIOPWMTON_HAS_OUT 1
#define PIOPWMTON_HAS_TRI 0
#define PIOPWMTON_IRQ -1
#define PIOPWMTON_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIOPWMTON_IRQ_TYPE "NONE"
#define PIOPWMTON_NAME "/dev/pioPwmTon"
#define PIOPWMTON_RESET_VALUE 0
#define PIOPWMTON_SPAN 16
#define PIOPWMTON_TYPE "altera_avalon_pio"


/*
 * pioSW configuration
 *
 */

#define ALT_MODULE_CLASS_pioSW altera_avalon_pio
#define PIOSW_BASE 0x80010a0
#define PIOSW_BIT_CLEARING_EDGE_REGISTER 0
#define PIOSW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIOSW_CAPTURE 1
#define PIOSW_DATA_WIDTH 13
#define PIOSW_DO_TEST_BENCH_WIRING 0
#define PIOSW_DRIVEN_SIM_VALUE 0
#define PIOSW_EDGE_TYPE "ANY"
#define PIOSW_FREQ 100000000
#define PIOSW_HAS_IN 1
#define PIOSW_HAS_OUT 0
#define PIOSW_HAS_TRI 0
#define PIOSW_IRQ 3
#define PIOSW_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIOSW_IRQ_TYPE "LEVEL"
#define PIOSW_NAME "/dev/pioSW"
#define PIOSW_RESET_VALUE 0
#define PIOSW_SPAN 16
#define PIOSW_TYPE "altera_avalon_pio"


/*
 * pll configuration
 *
 */

#define ALT_MODULE_CLASS_pll altpll
#define PLL_BASE 0x80010b0
#define PLL_IRQ -1
#define PLL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PLL_NAME "/dev/pll"
#define PLL_SPAN 16
#define PLL_TYPE "altpll"


/*
 * sdramController configuration
 *
 */

#define ALT_MODULE_CLASS_sdramController altera_avalon_new_sdram_controller
#define SDRAMCONTROLLER_BASE 0x0
#define SDRAMCONTROLLER_CAS_LATENCY 3
#define SDRAMCONTROLLER_CONTENTS_INFO
#define SDRAMCONTROLLER_INIT_NOP_DELAY 0.0
#define SDRAMCONTROLLER_INIT_REFRESH_COMMANDS 2
#define SDRAMCONTROLLER_IRQ -1
#define SDRAMCONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAMCONTROLLER_IS_INITIALIZED 1
#define SDRAMCONTROLLER_NAME "/dev/sdramController"
#define SDRAMCONTROLLER_POWERUP_DELAY 200.0
#define SDRAMCONTROLLER_REFRESH_PERIOD 7.8125
#define SDRAMCONTROLLER_REGISTER_DATA_IN 1
#define SDRAMCONTROLLER_SDRAM_ADDR_WIDTH 0x19
#define SDRAMCONTROLLER_SDRAM_BANK_WIDTH 2
#define SDRAMCONTROLLER_SDRAM_COL_WIDTH 10
#define SDRAMCONTROLLER_SDRAM_DATA_WIDTH 32
#define SDRAMCONTROLLER_SDRAM_NUM_BANKS 4
#define SDRAMCONTROLLER_SDRAM_NUM_CHIPSELECTS 1
#define SDRAMCONTROLLER_SDRAM_ROW_WIDTH 13
#define SDRAMCONTROLLER_SHARED_DATA 0
#define SDRAMCONTROLLER_SIM_MODEL_BASE 0
#define SDRAMCONTROLLER_SPAN 134217728
#define SDRAMCONTROLLER_STARVATION_INDICATOR 0
#define SDRAMCONTROLLER_TRISTATE_BRIDGE_SLAVE ""
#define SDRAMCONTROLLER_TYPE "altera_avalon_new_sdram_controller"
#define SDRAMCONTROLLER_T_AC 5.5
#define SDRAMCONTROLLER_T_MRD 3
#define SDRAMCONTROLLER_T_RCD 20.0
#define SDRAMCONTROLLER_T_RFC 70.0
#define SDRAMCONTROLLER_T_RP 20.0
#define SDRAMCONTROLLER_T_WR 14.0


/*
 * systemTimer configuration
 *
 */

#define ALT_MODULE_CLASS_systemTimer altera_avalon_timer
#define SYSTEMTIMER_ALWAYS_RUN 0
#define SYSTEMTIMER_BASE 0x8001020
#define SYSTEMTIMER_COUNTER_SIZE 32
#define SYSTEMTIMER_FIXED_PERIOD 0
#define SYSTEMTIMER_FREQ 100000000
#define SYSTEMTIMER_IRQ 1
#define SYSTEMTIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYSTEMTIMER_LOAD_VALUE 99999
#define SYSTEMTIMER_MULT 0.001
#define SYSTEMTIMER_NAME "/dev/systemTimer"
#define SYSTEMTIMER_PERIOD 1
#define SYSTEMTIMER_PERIOD_UNITS "ms"
#define SYSTEMTIMER_RESET_OUTPUT 0
#define SYSTEMTIMER_SNAPSHOT 1
#define SYSTEMTIMER_SPAN 32
#define SYSTEMTIMER_TICKS_PER_SEC 1000
#define SYSTEMTIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYSTEMTIMER_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
