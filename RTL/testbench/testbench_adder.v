`include "../define/main.def.v"

`timescale 1ns/1ps
module testbench_adder();

    reg en;
    reg DUT_clk;
    reg DUT_hclk;
    reg DUT_rst_n;
    reg DUT_en;
    reg DUT_valid;
    reg [`LEN_DATA - 1:0] DUT_a;
    reg [`LEN_DATA - 1:0] DUT_b;
    reg [`LEN_DATA - 1:0] DUT_imm;
    reg [7:0] DUT_cin;
    reg [`LEN_TYPE_ALU - 1:0] DUT_code;
    reg [7:0] DUT_cmsk_n;
    wire [`LEN_DATA - 1:0] DUT_sum;
    wire [`LEN_DATA - 1:0] DUT_result;
    wire [`LEN_DATA - 1:0] DUT_ex_result;
    wire DUT_cout;
    wire DUT_rdy;
    always #1 DUT_clk = ~DUT_clk;
    always #2 DUT_hclk = ~DUT_hclk;
    alu DUT_alu(
        .rst_n  (DUT_rst_n  ),
        .clk    (DUT_clk    ),
        .en     (DUT_en     ),
        .a      (DUT_a      ),
        .b      (DUT_b      ),      
        .imm    (DUT_imm    ),
        .cin    (DUT_cin    ),
        .code   (DUT_code   ),
        .result (DUT_result ),
        .ex_result(DUT_ex_result),
        .cout   (DUT_cout   ),
        .rdy    (DUT_rdy    )
    );
    initial begin
        en         = 1'b0;
        DUT_clk    = 1'b0;
        DUT_hclk   = 1'b0;
        DUT_rst_n  = 1'b0;
        DUT_en     = 1'b0;
        DUT_valid  = 1'b0;
        DUT_a      = {`LEN_DATA{1'b0}};
        DUT_b      = {`LEN_DATA{1'b0}};
        DUT_imm    = {`LEN_DATA{1'b0}};
        DUT_cin    = 1'b0;
        DUT_code   = {`LEN_TYPE_ALU{1'b0}};
        DUT_cmsk_n = 8'h00;
        #34
        en         = 1'b1;
        DUT_rst_n   = 1'b1;
        DUT_en     = 1'b1;
        #1000
        $finish;
    end
    always @(posedge DUT_hclk or negedge DUT_hclk) begin
        if(en) begin
            if(DUT_hclk) begin
                DUT_valid  = 1'b1;
                DUT_a      = {32'b0, $random};
                DUT_b      = {32'b0, $random};
                DUT_imm    = {32'b0, $random};
                DUT_code   = 5'b00_110;
                DUT_cin    = $random;
                DUT_cmsk_n = $random;
            end
            else begin
               DUT_valid  = 1'b0; 
            end
        end
    end
endmodule