`include "../define/main.def.v"

`timescale 1ns/1ps
module testbench();

    reg DUT_clk;
    reg DUT_rst;
    reg DUT_en;
    reg [`LEN_DATA - 1:0] DUT_a;
    reg [`LEN_DATA - 1:0] DUT_b;
    wire [`LEN_DATA - 1:0] DUT_sum;
    wire DUT_rdy;
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
        DUT_rst = 1'b0;
        DUT_en  = 1'b0;
        DUT_a   = {`LEN_DATA{1'b0}};
        DUT_b   = {`LEN_DATA{1'b0}};
        #34
        DUT_rst = 1'b1;
        DUT_en  = 1'b1;
        #1
        DUT_a   = 912;
        DUT_b   = 65;

        #20
        DUT_a   = 768;
        DUT_b   = 65;
        #20
        DUT_a   = 65;
        DUT_b   = 65;
        #20
        DUT_a   = 456;
        DUT_b   = 999;
        #20
        DUT_a   = 64;
        DUT_b   = 65;
        #20
        DUT_a   = 6234;
        DUT_b   = 90213;
        #100
        $finish;
    end
    always #1 DUT_clk = ~DUT_clk;
    

endmodule