module pwmGenDe2_115 (
	CLOCK_50, KEY, SW, LEDR, GPIO,
	HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7,
	DRAM_DQ, DRAM_ADDR, DRAM_BA, DRAM_CAS_N, DRAM_CKE, DRAM_CS_N,
	DRAM_DQM, DRAM_RAS_N, DRAM_WE_N, DRAM_CLK,
	LCD_RS, LCD_RW, LCD_EN, LCD_DATA
);

input          CLOCK_50;   // 50 MHz system clock source
input  [3:0]   KEY;        // Pushbuttons
input  [17:0]  SW;         // Switches
output [17:0]  LEDR;       // Red LEDs
output [6:0]   HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7; // 7-Segment Displays
inout  [35:0]  GPIO;       // GPIO headers

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

// Diviseur horloge 50MHz -> 1MHz (période = 1µs)
reg [5:0] div_cnt = 0;
reg clk_1M = 0;
always @(posedge CLOCK_50) begin
    if (div_cnt == 24) begin // 25 cycles haut, 25 bas
        div_cnt <= 0;
        clk_1M <= ~clk_1M;
    end else begin
        div_cnt <= div_cnt + 1;
    end
end

// Signal test ~1kHz (1MHz / 1024) sur GPIO[35]
reg [9:0] clk_1k_cnt = 0;
always @(posedge clk_1M) begin
    clk_1k_cnt <= clk_1k_cnt + 1;
end
assign GPIO[35] = clk_1k_cnt[9]; // Bascule sur bit de poids fort

// Câblage bus internes (Qsys <-> modMultiPWM)
wire [31:0] hex_bus;
wire [9:0]  pwm_ton;
wire [23:0] pwm_nlatch;
wire [23:0] pwm_oe;
wire [12:0] led_bus;

// Assignations LEDs : mapping bus Qsys et forçage 0 pour LEDs inutilisées
assign LEDR[12:0] = led_bus;
assign LEDR[17:13] = 5'b00000;

// Instanciation système Qsys
pwmGen u0 (
    .clk_clk           (CLOCK_50),   //        clk.clk
    .lcd_RS            (LCD_RS),     //        lcd.RS
    .lcd_RW            (LCD_RW),     //           .RW
    .lcd_data          (LCD_DATA),   //           .data
    .lcd_E             (LCD_EN),     //           .E
    .reset_reset_n     (sys_reset_n),//      reset.reset_n
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
    .sw_export         (SW[12:0]),         //         sw.export
    .key_export        (KEY[3:0]),         //        key.export
    .hex_export        (hex_bus),          //        hex.export
    .pwm_ton_export    (pwm_ton),          //    pwm_ton.export
    .pwm_nlatch_export (pwm_nlatch),       // pwm_nlatch.export
    .pwm_oe_export     (pwm_oe),           //     pwm_oe.export
    .led_export        (led_bus)           //        led.export
);

// Instanciation bloc 24 PWM 10-bit
modMultiPWM #(
    .NB_PWM(24),
    .RESOLUTION(10)
) pwm_inst (
    .ClkIn({24{clk_1M}}), // Réplication horloge 1MHz
    .PWMout(GPIO[23:0]),
    .nLatch(pwm_nlatch),
    .Ton(pwm_ton),
    .oe(pwm_oe)
);

// Décodeurs BCD vers 7 segments (4 bits par afficheur)
// 0xF est utilisé comme code d'extinction
hex2seg h0(hex_bus[3:0],   HEX0);
hex2seg h1(hex_bus[7:4],   HEX1);
hex2seg h2(hex_bus[11:8],  HEX2);
hex2seg h3(hex_bus[15:12], HEX3);
hex2seg h4(hex_bus[19:16], HEX4);
hex2seg h5(hex_bus[23:20], HEX5);
hex2seg h6(hex_bus[27:24], HEX6);
hex2seg h7(hex_bus[31:28], HEX7);

endmodule

// Décodeur logique combinatoire (actif bas, anode commune)
module hex2seg(input [3:0] bin, output reg [6:0] seg);
    always @(*) begin
        case(bin)
            // Inverseur bit à bit (~)
            4'h0: seg = ~7'h3F;
            4'h1: seg = ~7'h06;
            4'h2: seg = ~7'h5B;
            4'h3: seg = ~7'h4F;
            4'h4: seg = ~7'h66;
            4'h5: seg = ~7'h6D;
            4'h6: seg = ~7'h7D;
            4'h7: seg = ~7'h07;
            4'h8: seg = ~7'h7F;
            4'h9: seg = ~7'h6F;
            4'hA: seg = ~7'h77;
            4'hB: seg = ~7'h7C;
            4'hC: seg = ~7'h39;
            4'hD: seg = ~7'h5E;
            4'hE: seg = ~7'h79;
            4'hF: seg = ~7'h00; // Eteint
            default: seg = ~7'h00;
        endcase
    end
endmodule