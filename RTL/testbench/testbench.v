`include "../define/main.def.v"

`timescale 1ns/1ps
module testbench();

    reg DUT_clk;
    reg DUT_hclk;
    reg DUT_rst;
    reg DUT_en;
    reg [`LEN_DATA - 1:0] DUT_a;
    reg [`LEN_DATA - 1:0] DUT_b;
    wire [`LEN_DATA - 1:0] DUT_sum;
    wire DUT_rdy;
    always #1 DUT_clk = ~DUT_clk;
    always #20 DUT_hclk = ~DUT_hclk;
    adder64 DUT_adder(
        .rst    (DUT_rst    ),
        .clk    (DUT_clk    ),
        .en     (DUT_en     ),
        .a      (DUT_a      ),
        .b      (DUT_b      ),
        .sum    (DUT_sum    ),
        .rdy    (DUT_rdy    )
    );
    initial begin
        DUT_clk = 1'b0;
        DUT_hclk = 1'b0;
        DUT_rst = 1'b0;
        DUT_en  = 1'b0;
        DUT_a   = {`LEN_DATA{1'b0}};
        DUT_b   = {`LEN_DATA{1'b0}};
        #34
        DUT_rst = 1'b1;
        DUT_en  = 1'b1;
        #1000
        $finish;
    end
    always @(posedge DUT_clk) begin
        DUT_a = $random;// & 64'hff;
        DUT_b = $random;// & 64'hff;
    end

endmodule