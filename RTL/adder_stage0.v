`include "main.def.v"

module adder_stage0(
    input wire [LEN_DATA - 1:0] A,
    input wire [LEN_DATA - 1:0] B,
    output wire [LEN_DATA - 1:0] gen_out,
    output wire [LEN_DATA - 1:0] prop_out
);
    wire [LEN_DATA - 1:0] generate_in;
    wire [LEN_DATA - 1:0] propogate_in;
    generate;
        for (int i=0; i<LEN_DATA; i = i + 1) begin : stage0
            generate_in[i] = A[i] & B[i];
            propogate_in[i] = A[i] ^ B[i];
        end
    endgenerate
    assign gen_out = generate_in;
    assign prop_out = propogate_in;
endmodule