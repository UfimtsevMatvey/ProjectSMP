`include "../define/main.def.v"

module adder_stage7(
    input wire [`LEN_DATA - 1:0] generate_in,
    input wire [`LEN_DATA - 1:0] propogate_in,
    output wire [`LEN_DATA - 1:0] generate_out,
    output wire [`LEN_DATA - 1:0] propogate_out
);
    wire [`LEN_DATA - 1:0] g_in;
    wire [`LEN_DATA - 1:0] p_in;
    wire [`LEN_DATA - 1:0] g_out;
    wire [`LEN_DATA - 1:0] p_out;

    assign g_in = generate_in;
    assign p_in = propogate_in;
    
    generate
        genvar i;
        for (i = 32; i < `LEN_DATA; i = i + 1) begin : stage7_32odd
            gp_cell gpcell(
                .g_left (g_in   [i]     ),
                .g_right(g_in   [31]    ),
                .p_left (p_in   [i]     ),
                .p_right(p_in   [31]    ),
                .g_out  (g_out  [i]     ),
                .p_out  (p_out  [i]     )
            );
        end
        for (i = 0; i < `LEN_DATA/2; i = i + 1) begin : stage7_32ever
            assign g_out[i] = g_in[i];
            assign p_out[i] = p_in[i];
        end
    endgenerate
    assign generate_out = g_out;
    assign propogate_out = p_out;
endmodule