`include "define/main.def.v"

module adder64(
    input wire rst,
    input wire clk,
    input wire en,// enable module
    input wire valid,//valid data for adder
    input wire [`LEN_DATA - 1:0] a,
    input wire [`LEN_DATA - 1:0] b,
    input wire cin,
    input wire [7:0] cmsk_n,
    output reg [`LEN_DATA - 1:0] sum,
    output reg cout,
    output reg rdy
);
wire [`LEN_DATA - 1:0] p_pipeline [9:0];
wire [`LEN_DATA - 1:0] g_pipeline [9:0];
wire [7:0] carry_mask_pipeline_n [9:0];
wire [`LEN_DATA - 1:0] a_reg;
wire [`LEN_DATA - 1:0] b_reg;
wire cin_reg;
reg [`LEN_DATA - 1:0] carry;
wire [`LEN_DATA - 1:0] axorb_pipeline [9:0];
wire rdy_pipeline [9:0];

wire [`LEN_DATA - 1:0] res;
//init pipeline
assign axorb_pipeline[0] = a_reg ^ b_reg;
assign carry_mask_pipeline_n[0] = cmsk_n;
//bit mask for carry
always @(*) begin
    carry        = (g_pipeline[8][`LEN_DATA - 1:0] << 1) ^  {{`LEN_DATA{1'b0}},g_pipeline[8][0]};
    carry[0]     = carry[0]    & carry_mask_pipeline_n[8][0];
    carry[8]     = carry[8]    & carry_mask_pipeline_n[8][1];
    carry[16]    = carry[16]   & carry_mask_pipeline_n[8][2];
    carry[24]    = carry[24]   & carry_mask_pipeline_n[8][3];
    carry[32]    = carry[32]   & carry_mask_pipeline_n[8][4];
    carry[40]    = carry[40]   & carry_mask_pipeline_n[8][5];
    carry[48]    = carry[48]   & carry_mask_pipeline_n[8][6];
    carry[56]    = carry[56]   & carry_mask_pipeline_n[8][7];
    sum          = axorb_pipeline[8] ^ carry;
    cout         = g_pipeline[8][`LEN_DATA - 1];
    rdy          = rdy_pipeline[8];
end

//assign sum = axorb_pipeline[8] ^ carry;
//assign cout = g_pipeline[7][`LEN_DATA - 1];
/*
    If valid is asserted, then rdy will be aserted after 9 clock time
*/
register #(.width(1))
    reg_rdy
    (
        .rst(rst),
        .clk(clk),
        .en(1'b1),
        .d(valid),
        .q(rdy_pipeline[0])
    );
genvar j;
generate
    for(j = 0; j < 9; j = j + 1) begin : ready_pipeline
    register #(.width(1))
        reg_rdy
        (
            .rst(rst),
            .clk(clk),
            .en(1'b1),
            .d(rdy_pipeline[j]),
            .q(rdy_pipeline[j + 1])
        );
    end
    
endgenerate
    //data pipeline
register #(.width(2*`LEN_DATA + 1))
    reg_data0
    (
        .rst(rst),
        .clk(clk),
        .en(en),
        .d({a, b, cin}),
        .q({a_reg, b_reg, cin_reg})
    );
genvar i;
//pipeline for a ^ b and carry mask
generate
    for(i = 0; i < 9; i = i + 1) begin : data_pipeline  
    register #(.width(`LEN_DATA))
        reg_data_axorb
        (
            .rst(rst),
            .clk(clk),
            .en(en),
            .d(axorb_pipeline[i    ]),
            .q(axorb_pipeline[i + 1])
        );
    register #(.width(8))
        reg_data_carry_mask
        (
            .rst(rst),
            .clk(clk),
            .en(en),
            .d(carry_mask_pipeline_n[i    ]),
            .q(carry_mask_pipeline_n[i + 1])
        );
    end
endgenerate
    //adder pipeline
wire [`LEN_DATA - 1:0] gen_stage0;
wire [`LEN_DATA - 1:0] prop_stage0;
adder_stage0 
    adder_stage0
    (
        .A(a_reg),
        .B(b_reg),
        .Cin(cin_reg),
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
        .q({g_pipeline[1], p_pipeline[1]})
    );


wire [`LEN_DATA - 1:0] gen_stage1;
wire [`LEN_DATA - 1:0] prop_stage1;
adder_stage1 
    adder_stage1
    (
        .generate_in(g_pipeline[1]),
        .propogate_in(p_pipeline[1]),
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
        .q({g_pipeline[2], p_pipeline[2]})
    );


wire [`LEN_DATA - 1:0] gen_stage2;
wire [`LEN_DATA - 1:0] prop_stage2;
adder_stage2 
    adder_stage2
    (
        .generate_in(g_pipeline[2]),
        .propogate_in(p_pipeline[2]),
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
        .q({g_pipeline[3], p_pipeline[3]})
    );


wire [`LEN_DATA - 1:0] gen_stage3;
wire [`LEN_DATA - 1:0] prop_stage3;
adder_stage3 
    adder_stage3
    (
        .generate_in(g_pipeline[3]),
        .propogate_in(p_pipeline[3]),
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
        .q({g_pipeline[4], p_pipeline[4]})
    );


wire [`LEN_DATA - 1:0] gen_stage4;
wire [`LEN_DATA - 1:0] prop_stage4;
adder_stage4 
    adder_stage4
    (
        .generate_in(g_pipeline[4]),
        .propogate_in(p_pipeline[4]),
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
        .q({g_pipeline[5], p_pipeline[5]})
    );

wire [`LEN_DATA - 1:0] gen_stage5;
wire [`LEN_DATA - 1:0] prop_stage5;
adder_stage5 
    adder_stage5
    (
        .generate_in(g_pipeline[5]),
        .propogate_in(p_pipeline[5]),
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
        .q({g_pipeline[6], p_pipeline[6]})
    );


wire [`LEN_DATA - 1:0] gen_stage6;
wire [`LEN_DATA - 1:0] prop_stage6;
adder_stage6
    adder_stage6
    (
        .generate_in(g_pipeline[6]),
        .propogate_in(p_pipeline[6]),
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
        .q({g_pipeline[7], p_pipeline[7]})
    );


wire [`LEN_DATA - 1:0] gen_stage7;
wire [`LEN_DATA - 1:0] prop_stage7;
adder_stage7
    adder_stage7
    (
        .generate_in(g_pipeline[7]),
        .propogate_in(p_pipeline[7]),
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
        .q({g_pipeline[8], p_pipeline[8]})
    );
endmodule