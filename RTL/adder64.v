`include "define/main.def.v"

module adder64(
    input wire rst,
    input wire clk,
    input wire en,
    input wire [`LEN_DATA - 1:0] a,
    input wire [`LEN_DATA - 1:0] b,
    output [`LEN_DATA - 1:0] sum,
    output reg rdy
);
wire [`LEN_DATA - 1:0] p_pipeline [9:0];
wire [`LEN_DATA - 1:0] g_pipeline [9:0];
wire [`LEN_DATA - 1:0] a_reg;
wire [`LEN_DATA - 1:0] b_reg;

wire [`LEN_DATA - 1:0] res;
wire [`LEN_DATA - 1:0] sres;
assign res = (g_pipeline[7][`LEN_DATA - 1:0]<<1) ^ a_reg ^ b_reg;
register #(.width(`LEN_DATA))
    reg_sum 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d(res),
        .q(sum)
    );
register #(.width(2*`LEN_DATA))
    reg_data 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({a, b}),
        .q({a_reg, b_reg})
    );
wire [`LEN_DATA - 1:0] gen_stage0;
wire [`LEN_DATA - 1:0] prop_stage0;
adder_stage0 
    adder_stage0
    (
        .A(a_reg),
        .B(b_reg),
        .gen_out(gen_stage0),
        .prop_out(prop_stage0)
    );
register #(.width(2*`LEN_DATA)) 
    reg_stage0 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage0, prop_stage0}),
        .q({g_pipeline[0], p_pipeline[0]})
    );


wire [`LEN_DATA - 1:0] gen_stage1;
wire [`LEN_DATA - 1:0] prop_stage1;
adder_stage1 
    adder_stage1
    (
        .generate_in(g_pipeline[0]),
        .propogate_in(p_pipeline[0]),
        .generate_out(gen_stage1),
        .propogate_out(prop_stage1)
    );
register #(.width(2*`LEN_DATA)) 
    reg_stage1 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage1, prop_stage1}),
        .q({g_pipeline[1], p_pipeline[1]})
    );


wire [`LEN_DATA - 1:0] gen_stage2;
wire [`LEN_DATA - 1:0] prop_stage2;
adder_stage2 
    adder_stage2
    (
        .generate_in(g_pipeline[1]),
        .propogate_in(p_pipeline[1]),
        .generate_out(gen_stage2),
        .propogate_out(prop_stage2)
    );
register #(.width(2*`LEN_DATA))
    reg_stage2 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage2, prop_stage2}),
        .q({g_pipeline[2], p_pipeline[2]})
    );


wire [`LEN_DATA - 1:0] gen_stage3;
wire [`LEN_DATA - 1:0] prop_stage3;
adder_stage3 
    adder_stage3
    (
        .generate_in(g_pipeline[2]),
        .propogate_in(p_pipeline[2]),
        .generate_out(gen_stage3),
        .propogate_out(prop_stage3)
    );
register #(.width(2*`LEN_DATA))
    reg_stage3 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage3, prop_stage3}),
        .q({g_pipeline[3], p_pipeline[3]})
    );


wire [`LEN_DATA - 1:0] gen_stage4;
wire [`LEN_DATA - 1:0] prop_stage4;
adder_stage4 
    adder_stage4
    (
        .generate_in(g_pipeline[3]),
        .propogate_in(p_pipeline[3]),
        .generate_out(gen_stage4),
        .propogate_out(prop_stage4)
    );
register #(.width(2*`LEN_DATA))
    reg_stage4 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage4, prop_stage4}),
        .q({g_pipeline[4], p_pipeline[4]})
    );

wire [`LEN_DATA - 1:0] gen_stage5;
wire [`LEN_DATA - 1:0] prop_stage5;
adder_stage5 
    adder_stage5
    (
        .generate_in(g_pipeline[4]),
        .propogate_in(p_pipeline[4]),
        .generate_out(gen_stage5),
        .propogate_out(prop_stage5)
    );
register #(.width(2*`LEN_DATA))
    reg_stage5
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage5, prop_stage5}),
        .q({g_pipeline[5], p_pipeline[5]})
    );


wire [`LEN_DATA - 1:0] gen_stage6;
wire [`LEN_DATA - 1:0] prop_stage6;
adder_stage6
    adder_stage6
    (
        .generate_in(g_pipeline[5]),
        .propogate_in(p_pipeline[5]),
        .generate_out(gen_stage6),
        .propogate_out(prop_stage6)
    );
register #(.width(2*`LEN_DATA)) 
    reg_stage6
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage6, prop_stage6}),
        .q({g_pipeline[6], p_pipeline[6]})
    );


wire [`LEN_DATA - 1:0] gen_stage7;
wire [`LEN_DATA - 1:0] prop_stage7;
adder_stage7
    adder_stage7
    (
        .generate_in(g_pipeline[6]),
        .propogate_in(p_pipeline[6]),
        .generate_out(gen_stage7),
        .propogate_out(prop_stage7)
    );
register #(.width(2*`LEN_DATA))
    reg_stage7 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage7, prop_stage7}),
        .q({g_pipeline[7], p_pipeline[7]})
    );


//wire [`LEN_DATA - 1:0] gen_stage8;
//wire [`LEN_DATA - 1:0] prop_stage8;
/*adder_stage8 
    adder_stage8
    (
        .generate_in(g_pipeline[7]),
        .propogate_in(p_pipeline[7]),
        .generate_out(gen_stage8),
        .propogate_out(prop_stage8)
    );
register #(.width(2*`LEN_DATA))
    reg_stage8 
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({gen_stage8, prop_stage8}),
        .q({g_pipeline[8], p_pipeline[8]})
    );
*/
endmodule