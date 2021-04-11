`include "../define/main.def.v"
`define ALU_ADD64   5'b00001
`define ALU_ADC64   5'b00010
`define ALU_ADD32   5'b00011
`define ALU_ADD16   5'b00100
`define ALU_ADD8    5'b00101
`define ALU_SUB64   5'b00110
`define ALU_RSB64   5'b00111
`define ALU_SBC64   5'b01000
`define ALU_SUB32   5'b01001
`define ALU_SUB16   5'b01010
`define ALU_SUB8    5'b01011

`define ALU_AND     5'b01100
`define ALU_EOR     5'b01101
`define ALU_ORR     5'b01110
`define ALU_TST     5'b01111
`define ALU_TEQ     5'b10000
`define ALU_CMP     5'b10001
`define ALU_CMN     5'b10010
`define ALU_MVN     5'b10011
`define ALU_LSL     5'b10100
`define ALU_LSR     5'b10101
`define ALU_ASR     5'b10110
`define ALU_RRX     5'b10111
`define ALU_ROR     5'b11000
`define ALU_BSWP    5'b11001
`define ALU_SWR     5'b11010

module alu(
    input rst,
    input clk,
    input wire en,
    input wire [LEN_DATA - 1:0] a,
    input wire [LEN_DATA - 1:0] b,
    input wire [LEN_DATA - 1:0] imm,
    input wire cin,
    input wire [LEN_TYPE_ALU - 1:0] code,
    output reg [LEN_DATA - 1:0] result,
    output reg [LEN_DATA - 1:0] ex_result;
    output reg cout,
    output reg rdy
);
reg [LEN_DATA - 1:0]    a_in;
reg [LEN_DATA - 1:0]    b_in;
reg [7:0]               bit_mask_in_n;
reg adder_l_en;
reg adder_h_en;
reg [LEN_DATA - 1:0]    result_out;
reg [LEN_DATA - 1:0]    result_adder_out;
reg [LEN_DATA - 1:0]    ex_result_out;
reg [LEN_DATA - 1:0]    ex_result_adder_out;
reg [LEN_DATA - 1:0] shift_arg;
reg [2:0] shift_code;
reg [5:0] shift_value;
reg shift_carry_out;
reg shift_carry_in;
reg [LEN_DATA - 1:0] shift_res;
reg shift_rdy;
always @(posedge clk) begin
    result <= adder_l_en ? result_adder_out : result_out;
    ex_result <= adder_h_en ? ex_result_adder_out : ex_result_out;
end
//generate control-signal for adder
always @(posedge clk) begin
    case (code)
        ALU_ADD64 : begin
            a_in <= a;
            b_in <= b;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b0;
            bit_mask_in_n <= 8'b1111_1111;
        end
        ALU_ADC64 : begin
            a_in <= a;
            b_in <= b;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= cin;
            bit_mask_in_n <= 8'b1111_1111;
        end
        ALU_ADD32 : begin
            a_in <= a;
            b_in <= b;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b0;
            bit_mask_in_n <= 8'b1110_1110;
        end
        ALU_ADD16 : begin
            a_in <= a;
            b_in <= b;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b0;
            bit_mask_in_n <= 8'b1010_1010;
        end
        ALU_ADD8 : begin
            a_in <= a;
            b_in <= b;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b0;
            bit_mask_in_n <= 8'b0000_0000;
        end
        ALU_SUB64 : begin
            a_in <= a;
            b_in <= ~b + 1;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b1;
            bit_mask_in_n <= ~8'b1111_1111;
        end
        ALU_RSB64 : begin
            a_in <= a;
            b_in <= b + 1;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b1 ^ cin;
            bit_mask_in_n <= ~8'b1111_1111;
        end
        ALU_SBC64 : begin
            a_in <= a;
            b_in <= b + 1;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b1;
            bit_mask_in_n <= ~8'b1111_1111;
        end
        ALU_SUB32 : begin
            a_in <= a;
            b_in[31:0] <= ~b[31:0] + 1;
            b_in[63:32] <= ~b[63:32] + 1;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b1;
            bit_mask_in_n <= 8'b1110_1110;
        end
        ALU_SUB16 : begin
            a_in <= a;
            b_in[15:0] <= ~b[15:0] + 1;
            b_in[31:16] <= ~b[31:16] + 1;
            b_in[47:32] <= ~b[47:32] + 1;
            b_in[63:48] <= ~b[63:48] + 1;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b1;
            bit_mask_in_n <= ~8'b1010_1010;
        end
        ALU_SUB8 : begin
            a_in <= a;
            b_in[7:0] <= ~b[7:0] + 1;
            b_in[15:8] <= ~b[15:8] + 1;
            b_in[23:16] <= ~b[23:16] + 1;
            b_in[31:24] <= ~b[31:24] + 1;
            b_in[39:32] <= ~b[39:32] + 1;
            b_in[47:40] <= ~b[47:40] + 1;
            b_in[55:48] <= ~b[55:48] + 1;
            b_in[63:56] <= ~b[63:56] + 1;
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b0;
            carry_in <= 1'b1;
            bit_mask_in_n <= ~8'b1010_1010;
        end
        ALU_AND : begin
            a_in <= 0;
            b_in <= 0;
            carry_in <= 0;
            bit_mask_in_n <= 8'b0000_0000;
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            result_out <= a & b;
        end
        ALU_ORR : begin
            a_in <= 0;
            b_in <= 0;
            carry_in <= 0;
            bit_mask_in_n <= 8'b0000_0000;
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            result_out <= a | b;
        end
        ALU_EOR : begin
            a_in <= 0;
            b_in <= 0;
            carry_in <= 0;
            bit_mask_in_n <= 8'b0000_0000;
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            result_out <= a ^ b;
        end
        ALU_MVN : begin
            a_in <= 0;
            b_in <= 0;
            carry_in <= 0;
            bit_mask_in_n <= 8'b0000_0000;
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            result_out <= ~a;
        end
        ALU_LSL : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            shift_code <= 0;
            shift_arg <= a;
            shift_value <= b[5:0];
            shift_carry_in <= 0;
            result_out <= shift_rdy ? shift_res : 0;
        end
        ALU_LSR : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            shift_code <= 1;
            shift_arg <= a;
            shift_value <= b[5:0];
            shift_carry_in <= 0;
            result_out <= shift_rdy ? shift_res : 0;
        end
        ALU_ASR : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            shift_code <= 2;
            shift_arg <= a;
            shift_value <= b[5:0];
            shift_carry_in <= cin;
            result_out <= shift_rdy ? shift_res : 0;
        end
        
        ALU_RRX : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            shift_code <= 3;
            shift_arg <= a;
            shift_value <= b[5:0];
            shift_carry_in <= cin;
            result_out <= shift_rdy ? shift_res : 0;
        end
        ALU_ROR : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            shift_code <= 4;
            shift_arg <= a;
            shift_value <= b[5:0];
            shift_carry_in <= 0;
            result_out <= shift_rdy ? shift_res : 0;
        end
        ALU_BSWP : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            result_out <= byte_swap(a);
        end
        ALU_SWR : begin
            adder_l_en <= 1'b0;
            adder_h_en <= 1'b0;
            result_out <= b;
            ex_result_out <= a;
        end
        //two step commands:
        ALU_ADD128_BYTE : begin
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b1;
            a_out <= a;
            b_out <= imm;
            bit_mask_out_n = 8'b0000_0000;
            carry_in <= 1'b0;
            ex_a_out <= b;
            ex_b_out = imm;
            ex_bit_mask_out_n = 8'b0000_0000;
            ex_carry_in <= 1'b0;
        end
        ALU_ADD128_TWOBYTE : begin
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b1;
            a_out <= a;
            b_out <= imm;
            bit_mask_out_n = 8'b0101_0101;
            carry_in <= 1'b0;
            ex_a_out <= b;
            ex_b_out = imm;
            ex_bit_mask_out_n = 8'b0101_0101;
            ex_carry_in <= 1'b0;
        end
        ALU_SUB128_BYTE : begin
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b1;
            a_out <= a;
            b_out[7:0] <= ~imm[7:0] + 1;
            b_out[15:8] <= ~imm[15:8] + 1;
            b_out[23:16] <= ~imm[23:16] + 1;
            b_out[31:24] <= ~imm[31:24] + 1;
            b_out[39:32] <= ~imm[39:32] + 1;
            b_out[47:40] <= ~imm[47:40] + 1;
            b_out[55:48] <= ~imm[55:48] + 1;
            b_out[63:56] <= ~imm[63:56] + 1;
            bit_mask_out_n = 8'b1111_1111;
            carry_in <= 1'b1;
            ex_a_out <= b;
            ex_b_out = imm;
            ex_bit_mask_out_n = 8'b1111_1111;
            ex_carry_in <= 1'b1;
        end
        ALU_SUB128_TWOBYTE : begin
            adder_l_en <= 1'b1;
            adder_h_en <= 1'b1;
            a_out <= a;
            b_out[15:0] <= ~imm[15:0] + 1;
            b_out[31:16] <= ~imm[31:16] + 1;
            b_out[47:32] <= ~imm[47:32] + 1;
            b_out[63:48] <= ~imm[63:48] + 1;
            bit_mask_out_n = ~8'b0101_0101;
            carry_in <= 1'b1;
            ex_a_out <= b;
            ex_b_out = imm;
            ex_bit_mask_out_n = ~8'b0101_0101;
            ex_carry_in <= 1'b1;
        end
        default: begin
            //default case
        end
    endcase
end
//Ladner-Fisher adder
adder64 adder_l(
    .rst    (rst    ),
    .clk    (clk    ),
    .en     (adder_l_en     ),
    .valid  (1'b1   ),
    .a      (a_out  ),
    .b      (b_out  ),
    .cin    (carry_out),
    .cmsk_n (bit_mask_out_n),
    .sum    (result_adder_out ),
    .cout   (cout   ),
    .rdy    (rdy    )
);
adder64 adder_h(
    .rst    (rst    ),
    .clk    (clk    ),
    .en     (adder_h_en     ),
    .valid  (1'b1   ),
    .a      (ex_a_out  ),
    .b      (ex_b_out  ),
    .cin    (ex_carry_out),
    .cmsk_n (ex_bit_mask_out_n),
    .sum    (ex_result_adder_out ),
    .cout   (ex_cout   ),
    .rdy    (ex_rdy    )
);

shift shifter(
    .rst        (rst),
    .a          (shift_arg),
    .c          (shift_value),
    .code       (shift_code),
    .carry      (shift_carry_in),
    .s_res      (shift_res),
    .carry_out  (shift_carry_out),
    .rst        (shift_rdy)
);

endmodule