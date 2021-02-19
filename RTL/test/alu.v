`include "define/main.def.v"

module alu(
    input rst,
    input clk,
    input wire en,
    input wire [LEN_DATA - 1:0] A,
    input wire [LEN_DATA - 1:0] B,
    input wire [LEN_DATA/2 - 1:0] Imm,
    input wire [LEN_TYPE_ALU - 1:0] code,
    output reg [LEN_DATA - 1:0] result
);
//Ladner-Fisher adder

endmodule