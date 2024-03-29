`include "../../define/main.def.v"

module adder_stage2(
    input wire [`LEN_DATA:0] generate_in,
    input wire [`LEN_DATA:0] propogate_in,
    input wire [`LEN_DATA:0] mask,
    output wire [`LEN_DATA:0] generate_out,
    output wire [`LEN_DATA:0] propogate_out
);
    wire [`LEN_DATA:0] g_in;
    wire [`LEN_DATA:0] p_in;
    wire [`LEN_DATA:0] g_out;
    wire [`LEN_DATA:0] p_out;

    assign g_in = generate_in;
    assign p_in = propogate_in;
    
    generate
        genvar i;
        genvar j;
        for (i = 1; i < `LEN_DATA + 1; i = i + 2) begin : stage2_odd
            gp_cell gpcell(
                .g_left (g_in   [i]     ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i]     ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i]     ),
                .p_out  (p_out  [i]     )
            );
        end
        for (j = 0; j < `LEN_DATA + 1; j = j + 2) begin : stage2_ever
            assign g_out[j] = g_in[j];
            assign p_out[j] = p_in[j];
        end
    endgenerate
    assign generate_out = g_out & mask;
    assign propogate_out = p_out & mask;
endmodule