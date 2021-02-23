`include "../define/main.def.v"

`timescale 1ns/1ps
module testbench();

    reg en;
    reg DUT_clk;
    reg DUT_hclk;
    reg DUT_rst;
    reg DUT_en;
    reg DUT_valid;
    reg [`LEN_DATA - 1:0] DUT_a;
    reg [`LEN_DATA - 1:0] DUT_b;
    wire [`LEN_DATA - 1:0] DUT_sum;
    wire DUT_rdy;
    always #1 DUT_clk = ~DUT_clk;
    always #2 DUT_hclk = ~DUT_hclk;
    adder64 DUT_adder(
        .rst    (DUT_rst    ),
        .clk    (DUT_clk    ),
        .en     (DUT_en     ),
        .valid  (DUT_valid  ),
        .a      (DUT_a      ),
        .b      (DUT_b      ),
        .sum    (DUT_sum    ),
        .rdy    (DUT_rdy    )
    );
    initial begin
        en = 1'b0;
        DUT_clk = 1'b0;
        DUT_hclk = 1'b0;
        DUT_rst = 1'b0;
        DUT_en  = 1'b0;
        DUT_valid = 1'b0;
        DUT_a   = {`LEN_DATA{1'b0}};
        DUT_b   = {`LEN_DATA{1'b0}};
        #34
        en = 1'b1;
        DUT_rst = 1'b1;
        DUT_en  = 1'b1;
        #1000
        $finish;
    end
    always @(posedge DUT_hclk or negedge DUT_hclk) begin
        if(en) begin
            if(DUT_hclk) begin
                DUT_valid = 1'b1;
                DUT_a = $random;// & 64'hff;
                DUT_b = $random;// & 64'hff;
            end
            else begin
               DUT_valid = 1'b0; 
            end
        end
    end
endmodule