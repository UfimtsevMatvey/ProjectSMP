`include "define/main.def.v"
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
    input wire [LEN_DATA - 1:0] A,
    input wire [LEN_DATA - 1:0] B,
    input wire [LEN_DATA/2 - 1:0] Imm,
    input wire [LEN_TYPE_ALU - 1:0] code,
    output reg [LEN_DATA - 1:0] result,
    output reg cout,
    output reg rdy
);
//Ladner-Fisher adder
adder64 adder(
    .rst    (rst    ),
    .clk    (clk    ),
    .en     (en     ),
    .valid  (1'b1   ),
    .a      (A      ),
    .b      (B      ),
    .cin    (       ),
    .cmsk_n (       ),
    .sum    (result ),
    .cout   (cout   ),
    .rdy    (rdy    )
);



endmodule