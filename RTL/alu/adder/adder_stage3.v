`include "../../define/main.def.v"

module adder_stage3(
    input wire [`LEN_DATA:0] generate_in,
    input wire [`LEN_DATA:0] propogate_in,
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
        for (i = 2; i < `LEN_DATA; i = i + 4) begin : stage3_2odd
            gp_cell gpcell0(
                .g_left (g_in   [i]     ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i]     ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i]     ),
                .p_out  (p_out  [i]     )
            );
            gp_cell gpcell1(
                .g_left (g_in   [i + 1] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 1] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 1] ),
                .p_out  (p_out  [i + 1] )
            );
        end
        for (j = 0; j < `LEN_DATA; j = j + 4) begin : stage3_2ever
            assign g_out[j] = g_in[j];
            assign g_out[j + 1] = g_in[j + 1];
            assign p_out[j] = p_in[j];
            assign p_out[j + 1] = p_in[j + 1];
        end
        assign g_out[`LEN_DATA] = g_in[`LEN_DATA];
        assign p_out[`LEN_DATA] = p_in[`LEN_DATA];
    endgenerate
    assign generate_out = g_out;
    assign propogate_out = p_out;
endmodule