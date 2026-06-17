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
    .reset_reset_n     (sys_reset_n),//        reset.reset_n
    .sdram_clock_clk   (DRAM_CLK),   //  sdram_clock.clk
    .sdram_wire_addr   (DRAM_ADDR),  //   sdram_wire.addr
    .sdram_wire_ba     (DRAM_BA),    //             .ba
    .sdram_wire_cas_n  (DRAM_CAS_N), //             .cas_n
    .sdram_wire_cke    (DRAM_CKE),   //             .cke
    .sdram_wire_cs_n   (DRAM_CS_N),  //             .cs_n
    .sdram_wire_dq     (DRAM_DQ),    //             .dq
    .sdram_wire_dqm    (DRAM_DQM),   //             .dqm
    .sdram_wire_ras_n  (DRAM_RAS_N), //             .ras_n
    .sdram_wire_we_n   (DRAM_WE_N),  //             .we_n
    .lcd_external_RS   (LCD_RS),     // lcd_external.RS
    .lcd_external_RW   (LCD_RW),     //             .RW
    .lcd_external_data (LCD_DATA),   //             .data
    .lcd_external_E    (LCD_EN)      //             .E
);


endmodule