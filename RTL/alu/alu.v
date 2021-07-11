`include "../define/main.def.v"
`include "../define/alu.def.v"

module alu(
    input wire                       rst_n,
    input wire                       clk,
    input wire                       en,
    input wire [`LEN_DATA - 1:0]     a,
    input wire [`LEN_DATA - 1:0]     b,
    input wire [`LEN_DATA - 1:0]     imm,
    input wire [7:0]                 cin,
    input wire [`LEN_TYPE_ALU - 1:0] code,
    output reg [`LEN_DATA - 1:0]     result,
    output reg [`LEN_DATA - 1:0]     ex_result,
    output reg                       cout,
    output reg                       rdy
);
reg  [`LEN_DATA - 1:0]    a_in;
reg  [`LEN_DATA - 1:0]    b_in;
reg  [`LEN_DATA - 1:0]    ex_a_in;
reg  [`LEN_DATA - 1:0]    ex_b_in;
reg  [7:0]                bit_mask_in_n;
reg  [7:0]                ex_bit_mask_in_n;
reg                       adder_l_en;
reg                       adder_h_en;
reg  [`LEN_DATA - 1:0]    result_out;
wire [`LEN_DATA - 1:0]    result_adder_out;
reg  [`LEN_DATA - 1:0]    ex_result_out;
wire [`LEN_DATA - 1:0]    ex_result_adder_out;
reg  [`LEN_DATA - 1:0]    shift_arg;
reg  [2:0]                shift_code;
reg  [5:0]                shift_value;
wire                      shift_carry_out;
reg                       shift_carry_in;
reg  [7:0]                carry_in;
wire                      carry_out;
reg  [7:0]                ex_carry_in;
wire                      ex_carry_out;
wire                      adder_rdy;
wire                      adder_ex_rdy;
wire [`LEN_DATA - 1:0]    shift_res;
reg                       shift_en;
wire                      shift_rdy;

function [`LEN_DATA - 1:0] byte_swap( input [`LEN_DATA - 1:0] word);
begin
    byte_swap[7:0]      = word[63:56];
    byte_swap[15:8]     = word[55:48];
    byte_swap[23:16]    = word[47:40];
    byte_swap[31:24]    = word[39:32];
    byte_swap[39:32]    = word[31:24];
    byte_swap[47:40]    = word[23:16];
    byte_swap[55:48]    = word[15:8];
    byte_swap[63:56]    = word[7:0];
end 
endfunction

always @(posedge clk) begin
    if(~rst_n) begin
        result    <= 0;
        ex_result <= 0;
        cout      <= 0;
        rdy       <= 0;
    end
    else begin
        result    <= adder_l_en ? result_adder_out    : result_out;
        ex_result <= adder_h_en ? ex_result_adder_out : ex_result_out;
        cout      <= shift_rdy  ? shift_carry_out     : (adder_l_en ? (adder_h_en ? ex_carry_out : carry_out) : 0);
        rdy       <= (adder_l_en ? (adder_h_en ? adder_rdy | adder_ex_rdy : rdy) : 0);
    end 
end
//generate control-signal for adder
always @(posedge clk) begin
    if(~rst_n) begin
        adder_l_en       <= 1'b0;
        adder_h_en       <= 1'b0;
        shift_en         <= 1'b0;
    end
    else begin
        case (code)
            `ALU_ADD64 : begin
                a_in             <= a;
                b_in             <= b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 1'b0;
                bit_mask_in_n    <= 8'b1111_1110;
                shift_en         <= 1'b0;
            end
            `ALU_ADC64 : begin
                a_in             <= a;
                b_in             <= b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= cin;
                bit_mask_in_n    <= 8'b1111_1111;
                shift_en         <= 1'b0;
            end
            `ALU_ADD32 : begin
                a_in             <= a;
                b_in             <= b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 1'b0;
                bit_mask_in_n    <= 8'b1110_1110;
                shift_en         <= 1'b0;
            end
            `ALU_ADD16 : begin
                a_in             <= a;
                b_in             <= b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b0;
                bit_mask_in_n    <= 8'b1010_1010;
                shift_en         <= 1'b0;
            end
            `ALU_ADD8 : begin
                a_in             <= a;
                b_in             <= b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b0;
                bit_mask_in_n    <= 8'b0000_0000;
                shift_en         <= 1'b0;
            end
            `ALU_SUB64 : begin
                a_in             <= a;
                b_in             <= ~b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b0000_0001;
                bit_mask_in_n    <= 8'b1111_1111;
                shift_en         <= 1'b0;
            end
            `ALU_RSB64 : begin
                a_in             <= a;
                b_in             <= ~b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b1 ^ cin;
                bit_mask_in_n    <= ~8'b1111_1111;
                shift_en         <= 1'b0;
            end
            `ALU_SBC64 : begin
                a_in             <= a;
                b_in             <= b;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b1;
                bit_mask_in_n    <= 8'b1111_1111;
                shift_en         <= 1'b0;
            end
            `ALU_SUB32 : begin
                a_in             <= a;
                b_in[31:0]       <= ~b[31:0] + 1;
                b_in[63:32]      <= ~b[63:32] + 1;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b1;
                bit_mask_in_n    <= 8'b1110_1110;
                shift_en         <= 1'b0;
            end
            `ALU_SUB16 : begin
                a_in             <= a;
                b_in[15:0]       <= ~b[15:0] + 1;
                b_in[31:16]      <= ~b[31:16] + 1;
                b_in[47:32]      <= ~b[47:32] + 1;
                b_in[63:48]      <= ~b[63:48] + 1;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b1;
                bit_mask_in_n    <= ~8'b1010_1010;
                shift_en         <= 1'b0;
            end
            `ALU_SUB8 : begin
                a_in             <= a;
                b_in[7:0]        <= ~b[7:0]   + 1;
                b_in[15:8]       <= ~b[15:8]  + 1;
                b_in[23:16]      <= ~b[23:16] + 1;
                b_in[31:24]      <= ~b[31:24] + 1;
                b_in[39:32]      <= ~b[39:32] + 1;
                b_in[47:40]      <= ~b[47:40] + 1;
                b_in[55:48]      <= ~b[55:48] + 1;
                b_in[63:56]      <= ~b[63:56] + 1;
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b0;
                carry_in         <= 8'b1;
                bit_mask_in_n    <= ~8'b1010_1010;
                shift_en         <= 1'b0;
            end
            `ALU_AND : begin
                a_in             <= 0;
                b_in             <= 0;
                carry_in         <= 0;
                bit_mask_in_n    <= 8'b0000_0000;
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                result_out       <= a & b;
                shift_en         <= 1'b0;
            end
            `ALU_ORR : begin
                a_in             <= 0;
                b_in             <= 0;
                carry_in         <= 0;
                bit_mask_in_n    <= 8'b0000_0000;
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                result_out       <= a | b;
                shift_en         <= 1'b0;
            end
            `ALU_EOR : begin
                a_in             <= 0;
                b_in             <= 0;
                carry_in         <= 0;
                bit_mask_in_n    <= 8'b0000_0000;
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                result_out       <= a ^ b;
                shift_en         <= 1'b0;
            end
            `ALU_MVN : begin
                a_in             <= 0;
                b_in             <= 0;
                carry_in         <= 0;
                bit_mask_in_n    <= 8'b0000_0000;
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                result_out       <= ~a;
                shift_en         <= 1'b0;
            end
            `ALU_LSL : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                shift_code       <= 0;
                shift_arg        <= a;
                shift_value      <= b[5:0];
                shift_carry_in   <= 0;
                result_out       <= shift_rdy ? shift_res : 0;
                shift_en         <= 1'b1;
            end
            `ALU_LSR : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                shift_code       <= 1;
                shift_arg        <= a;
                shift_value      <= b[5:0];
                shift_carry_in   <= 0;
                result_out       <= shift_rdy ? shift_res : 0;
                shift_en         <= 1'b1;
            end
            `ALU_ASR : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                shift_code       <= 2;
                shift_arg        <= a;
                shift_value      <= b[5:0];
                shift_carry_in   <= cin;
                result_out       <= shift_rdy ? shift_res : 0;
                shift_en         <= 1'b1;
            end
            
            `ALU_RRX : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                shift_code       <= 3;
                shift_arg        <= a;
                shift_value      <= b[5:0];
                shift_carry_in   <= cin;
                result_out       <= shift_rdy ? shift_res : 0;
                shift_en         <= 1'b1;
            end
            `ALU_ROR : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                shift_code       <= 4;
                shift_arg        <= a;
                shift_value      <= b[5:0];
                shift_carry_in   <= 0;
                result_out       <= shift_rdy ? shift_res : 0;
                shift_en         <= 1'b1;
            end
            `ALU_BSWP : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                result_out       <= byte_swap(a);
                shift_en         <= 1'b0;
            end
            `ALU_SWR : begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                result_out       <= b;
                ex_result_out    <= a;
                shift_en         <= 1'b1;
            end
            //two step commands:
            `ALU_ADD128_BYTE : begin
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b1;
                a_in             <= a;
                b_in             <= imm;
                bit_mask_in_n    <= 8'b0000_0000;
                carry_in         <= 8'b0;
                ex_a_in          <= b;
                ex_b_in          <= imm;
                ex_bit_mask_in_n <= 8'b0000_0000;
                ex_carry_in      <= 8'b0;
                shift_en         <= 1'b0;
            end
            `ALU_ADD128_TWOBYTE : begin
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b1;
                a_in             <= a;
                b_in             <= imm;
                bit_mask_in_n    <= 8'b0101_0101;
                carry_in         <= 8'b0;
                ex_a_in          <= b;
                ex_b_in          <= imm;
                ex_bit_mask_in_n <= 8'b0101_0101;
                ex_carry_in      <= 8'b0;
                shift_en         <= 1'b0;
            end
            `ALU_SUB128_BYTE : begin
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b1;
                a_in             <= a;
                b_in[7:0]        <= ~imm[7:0] + 1;
                b_in[15:8]       <= ~imm[15:8] + 1;
                b_in[23:16]      <= ~imm[23:16] + 1;
                b_in[31:24]      <= ~imm[31:24] + 1;
                b_in[39:32]      <= ~imm[39:32] + 1;
                b_in[47:40]      <= ~imm[47:40] + 1;
                b_in[55:48]      <= ~imm[55:48] + 1;
                b_in[63:56]      <= ~imm[63:56] + 1;
                bit_mask_in_n    <= 8'b1111_1111;
                carry_in         <= 8'b1;
                ex_a_in          <= b;
                ex_b_in          <= imm;
                ex_bit_mask_in_n <= 8'b1111_1111;
                ex_carry_in      <= 8'b1;
                shift_en         <= 1'b0;
            end
            `ALU_SUB128_TWOBYTE : begin
                adder_l_en       <= 1'b1;
                adder_h_en       <= 1'b1;
                a_in             <= a;
                b_in[15:0]       <= ~imm[15:0] + 1;
                b_in[31:16]      <= ~imm[31:16] + 1;
                b_in[47:32]      <= ~imm[47:32] + 1;
                b_in[63:48]      <= ~imm[63:48] + 1;
                bit_mask_in_n    <= ~8'b0101_0101;
                carry_in         <= 8'b1;
                ex_a_in          <= b;
                ex_b_in          <= imm;
                ex_bit_mask_in_n <= ~8'b0101_0101;
                ex_carry_in      <= 8'b1;
                shift_en         <= 1'b0;
            end
            default: begin
                adder_l_en       <= 1'b0;
                adder_h_en       <= 1'b0;
                shift_en         <= 1'b0;
            end
        endcase
    end 
end
//Ladner-Fisher adder
adder64 adder_l(
    .rst_n  (rst_n    ),
    .clk    (clk    ),
    .en     (adder_l_en     ),
    .valid  (1'b1   ),
    .a      (a_in  ),
    .b      (b_in  ),
    .cin    (carry_in),
    .cmsk_n (bit_mask_in_n),
    .sum    (result_adder_out ),
    .cout   (carry_out),
    .rdy    (adder_rdy    )
);
adder64 adder_h(
    .rst_n  (rst_n    ),
    .clk    (clk    ),
    .en     (adder_h_en     ),
    .valid  (1'b1   ),
    .a      (ex_a_in  ),
    .b      (ex_b_in  ),
    .cin    (ex_carry_in),
    .cmsk_n (ex_bit_mask_in_n),
    .sum    (ex_result_adder_out ),
    .cout   (ex_carry_out),
    .rdy    (adder_ex_rdy    )
);

shift shifter(
    .rst_n      (rst_n),
    .clk        (clk),
    .shift_en   (shift_en),
    .a          (shift_arg),
    .c          (shift_value),
    .code       (shift_code),
    .carry      (shift_carry_in),
    .s_res      (shift_res),
    .carry_out  (shift_carry_out),
    .rdy        (shift_rdy)
);
endmodule