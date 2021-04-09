`include "define/main.def.v"
`define ALU_ADD64   1
`define ALU_ADD32   2
`define ALU_ADD16   3
`define ALU_ADD8    4
`define ALU_SUB64   5
`define ALU_SUB32   6
`define ALU_SUB16   7
`define ALU_SUB8    8
`define ALU_AND     9
`define ALU_OR      10
`define ALU_XOR     11
`define ALU_ADD128  12
`define ALU_SUB128  13
/*
code:
    1   - add64
    2   - add32
    3   - add16
    4   - add8
    5   - sub64
    6   - sub32
    7   - sub16
    8   - sub8
    9   - and
    10  - or
    11  - xor
    12  - add128/2 imm
    13  - sub128/2 imm
*/
module alu(
    input rst,
    input clk,
    input wire en,
    input wire [LEN_DATA - 1:0] a,
    input wire [LEN_DATA - 1:0] a,
    input wire cin;
    input wire [LEN_DATA/2 - 1:0] imm,
    input wire [LEN_TYPE_ALU - 1:0] code,
    output reg [LEN_DATA - 1:0] result,
    output reg cout,
    output reg rdy
);
reg [LEN_DATA - 1:0]    a_in;
reg [LEN_DATA - 1:0]    b_in;
reg [7:0]               bit_mask_in_n;
reg                     carry_in;
reg                     addre_en;
reg [LEN_DATA - 1:0]    result_out;
reg [LEN_DATA - 1:0]    result_adder_out;
assign result = en ? result_adder_out : result_out;
//generate control-signal for adder
always @(*) begin
    case (code)
        ALU_ADD64 : begin
            a_in = a;
            b_in = b;
            addre_en = 1'b1;
            carry_in = cin;
            bit_mask_in_n = 8'b1111_1111;
        end
        ALU_ADD32 : begin
            a_in = a;
            b_in = b;
            addre_en = 1'b1;
            carry_in = 1'b0;
            bit_mask_in_n = 8'b1110_1110;
        end
        ALU_ADD16 : begin
            a_in = a;
            b_in = b;
            addre_en = 1'b1;
            carry_in = 1'b0;
            bit_mask_in_n = 8'b1010_1010;
        end
        ALU_ADD8 : begin
            a_in = a;
            b_in = b;
            addre_en = 1'b1;
            carry_in = 1'b0;
            bit_mask_in_n = 8'b0000_0000;
        end
        ALU_SUB64 : begin
            a_in = a;
            b_in = ~b + 1;
            addre_en = 1'b1;
            carry_in = 1'b1;
            bit_mask_in_n = 8'b1111_1111;
        end
        ALU_SUB32 : begin
            a_in = a;
            b_in[31:0] = ~b[31:0] + 1;
            b_in[63:32] = ~b[63:32] + 1;
            addre_en = 1'b1;
            carry_in = 1'b1;
            bit_mask_in_n = 8'b1110_1110;
        end
        ALU_SUB16 : begin
            a_in = a;
            b_in[15:0] = ~b[15:0] + 1;
            b_in[31:16] = ~b[31:16] + 1;
            b_in[47:32] = ~b[47:32] + 1;
            b_in[63:48] = ~b[63:48] + 1;
            addre_en = 1'b1;
            carry_in = 1'b1;
            bit_mask_in_n = 8'b1010_1010;
        end
        ALU_SUB8 : begin
            a_in = a;
            b_in[7:0] = ~b[7:0] + 1;
            b_in[15:8] = ~b[15:8] + 1;
            b_in[23:16] = ~b[23:16] + 1;
            b_in[31:24] = ~b[31:24] + 1;
            b_in[39:32] = ~b[39:32] + 1;
            b_in[47:40] = ~b[47:40] + 1;
            b_in[55:48] = ~b[55:48] + 1;
            b_in[63:56] = ~b[63:56] + 1;
            addre_en = 1'b1;
            carry_in = 1'b1;
            bit_mask_in_n = 8'b1010_1010;
        end
        ALU_AND : begin
            a_in = 0;
            b_in = 0;
            carry_in = 0;
            bit_mask_in_n = 8'b0000_0000;
            addre_en = 1'b0;
            result_out = a & b;
        end
        ALU_OR : begin
            a_in = 0;
            b_in = 0;
            carry_in = 0;
            bit_mask_in_n = 8'b0000_0000;
            addre_en = 1'b0;
            result_out = a | b;
        end
        ALU_XOR : begin
            a_in = 0;
            b_in = 0;
            carry_in = 0;
            bit_mask_in_n = 8'b0000_0000;
            addre_en = 1'b0;
            result_out = a ^ b;
        end
        //two step commands:
        ALU_ADD128 : begin
        end
        ALU_SUB128 : begin
        end
        default: begin
            //default case
        end
    endcase
end
//Ladner-Fisher adder
adder64 adder(
    .rst    (rst    ),
    .clk    (clk    ),
    .en     (en     ),
    .valid  (1'b1   ),
    .a      (a_out  ),
    .b      (b_out  ),
    .cin    (carry_out),
    .cmsk_n (bit_mask_out_n),
    .sum    (result_adder_out ),
    .cout   (cout   ),
    .rdy    (rdy    )
);



endmodule