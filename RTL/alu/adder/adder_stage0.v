`include "../../define/main.def.v"

module adder_stage0(
    input wire [`LEN_DATA:0] A,
    input wire [`LEN_DATA:0] B,
    input wire [7:0] cin,
    output wire [`LEN_DATA:0] gen_out,
    output wire [`LEN_DATA:0] prop_out
);
    wire [`LEN_DATA:0] generate_in;
    wire [`LEN_DATA:0] propogate_in;
    wire generate_low;
    wire propogate_low;
    generate
        genvar i;
        genvar j;
        for (i = 1; i < `LEN_DATA + 1; i = i + 1) begin : stage0
            if(i[2:0] != 3'b000) begin
                assign generate_in[i] = A[i-1] & B[i-1];
                assign propogate_in[i] = A[i-1] ^ B[i-1];
            end
        end
        for (j = 1; j < 8; j = j + 1) begin : stage0_carry_mask
            assign generate_in [8*j] = (A[8*j-1] & B[8*j-1]) | cin[j];
            assign propogate_in[8*j] = (A[8*j-1] ^ B[8*j-1]) | cin[j];
        end
        assign generate_in [0] = cin[0];
        assign propogate_in[0] = cin[0];
    endgenerate
    assign gen_out  = generate_in;
    assign prop_out = propogate_in;
endmodule