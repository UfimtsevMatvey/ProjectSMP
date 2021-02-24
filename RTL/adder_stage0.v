`include "define/main.def.v"

module adder_stage0(
    input wire [`LEN_DATA - 1:0] A,
    input wire [`LEN_DATA - 1:0] B,
    input wire Cin,
    output wire [`LEN_DATA - 1:0] gen_out,
    output wire [`LEN_DATA - 1:0] prop_out
);
    wire [`LEN_DATA - 1:0] generate_in;
    wire [`LEN_DATA - 1:0] propogate_in;
    wire generate_low;
    wire propogate_low;
    generate
        genvar i;
        for (i=0; i < `LEN_DATA; i = i + 1) begin : stage0
            assign generate_in[i] = A[i] & B[i];
            assign propogate_in[i] = A[i] ^ B[i];
        end
    endgenerate
    assign propogate_low = propogate_in[0] | Cin;
    assign generate_low = generate_in[0] | Cin;
    assign gen_out = {generate_in[`LEN_DATA - 1:1], generate_low};
    assign prop_out = {propogate_in[`LEN_DATA - 1:1], propogate_low};
endmodule