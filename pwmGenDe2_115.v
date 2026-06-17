module pwmGenDe2_115 (
	CLOCK_50, KEY, DRAM_DQ,
	DRAM_ADDR, DRAM_BA, DRAM_CAS_N, DRAM_CKE, DRAM_CS_N,
	DRAM_DQM, DRAM_RAS_N, DRAM_WE_N, DRAM_CLK,
	LCD_RS, LCD_RW, LCD_EN, LCD_DATA
);

input          CLOCK_50;   // 50 MHz system clock source
input  [3:0]   KEY;        // Pushbuttons for resets and inputs

inout  [31:0]  DRAM_DQ;    // SDRAM Bidirectional data bus lines

output [12:0]  DRAM_ADDR;  // SDRAM Address multiplexed bus
output [1:0]   DRAM_BA;    // SDRAM Bank Address selects
output         DRAM_CAS_N; // SDRAM Column Address Strobe command line
output         DRAM_CKE;   // SDRAM Clock Enable control pin
output         DRAM_CS_N;  // SDRAM Chip Select active-low line
output [3:0]   DRAM_DQM;   // SDRAM Data Mask byte-enables
output         DRAM_RAS_N; // SDRAM Row Address Strobe command line
output         DRAM_WE_N;  // SDRAM Write Enable command line
output         DRAM_CLK;

output         LCD_RS;
output         LCD_RW;
output         LCD_EN;
output [7:0]   LCD_DATA;

// Reset pendant 65535 cycles après la mise sous tension
reg [15:0] por_counter = 16'h0000;
reg sys_reset_n = 1'b0;
always @(posedge CLOCK_50) begin
    if (por_counter < 16'hFFFF) begin
        por_counter <= por_counter + 1'b1;
        sys_reset_n <= 1'b0;
     end else begin
        sys_reset_n <= 1'b1;
     end
end

pwmGen u0 (
    .clk_clk           (CLOCK_50),   //          clk.clk
    .lcd_RS            (LCD_RS),     //        lcd.RS
    .lcd_RW            (LCD_RW),     //           .RW
    .lcd_data          (LCD_DATA),   //           .data
    .lcd_E             (LCD_EN),     //           .E
    .reset_reset_n     (sys_reset_n),//        reset.reset_n
    .sdram_clk_clk     (DRAM_CLK),   //  sdram_clk.clk
    .sdram_addr        (DRAM_ADDR),        //      sdram.addr
    .sdram_ba          (DRAM_BA),          //           .ba
    .sdram_cas_n       (DRAM_CAS_N),       //           .cas_n
    .sdram_cke         (DRAM_CKE),         //           .cke
    .sdram_cs_n        (DRAM_CS_N),        //           .cs_n
    .sdram_dq          (DRAM_DQ),          //           .dq
    .sdram_dqm         (DRAM_DQM),         //           .dqm
    .sdram_ras_n       (DRAM_RAS_N),       //           .ras_n
    .sdram_we_n        (DRAM_WE_N),        //           .we_n
        .sw_export         (<connected-to-sw_export>),         //         sw.export
        .key_export        (<connected-to-key_export>),        //        key.export
        .hex_export        (<connected-to-hex_export>),        //        hex.export
        .pwm_ton_export    (<connected-to-pwm_ton_export>),    //    pwm_ton.export
        .pwm_nlatch_export (<connected-to-pwm_nlatch_export>), // pwm_nlatch.export
        .pwm_oe_export     (<connected-to-pwm_oe_export>),     //     pwm_oe.export
        .led_export        (<connected-to-led_export>)         //        led.export
);

endmodule