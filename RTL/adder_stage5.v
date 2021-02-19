`include "define/main.def.v"

module adder_stage5(
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
        for (i = 8; i < `LEN_DATA; i = i + 16) begin : stage5_8odd
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
            gp_cell gpcell2(
                .g_left (g_in   [i + 2] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 2] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 2] ),
                .p_out  (p_out  [i + 2] )
            );
            gp_cell gpcell3(
                .g_left (g_in   [i + 3] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 3] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 3] ),
                .p_out  (p_out  [i + 3] )
            );
            gp_cell gpcell4(
                .g_left (g_in   [i + 4] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 4] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 4] ),
                .p_out  (p_out  [i + 4] )
            );
            gp_cell gpcell5(
                .g_left (g_in   [i + 5] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 5] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 5] ),
                .p_out  (p_out  [i + 5] )
            );
            gp_cell gpcell6(
                .g_left (g_in   [i + 6] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 6] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 6] ),
                .p_out  (p_out  [i + 6] )
            );
            gp_cell gpcell7(
                .g_left (g_in   [i + 7] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 7] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 7] ),
                .p_out  (p_out  [i + 7] )
            );
        end
        for (i = 0; i < `LEN_DATA; i = i + 16) begin : stage5_8ever
            assign g_out[i] = g_in[i];
            assign g_out[i + 1] = g_in[i + 1];
            assign g_out[i + 2] = g_in[i + 2];
            assign g_out[i + 3] = g_in[i + 3];
            assign g_out[i + 4] = g_in[i + 4];
            assign g_out[i + 5] = g_in[i + 5];
            assign g_out[i + 6] = g_in[i + 6];
            assign g_out[i + 7] = g_in[i + 7];
            
            assign p_out[i] = p_in[i];
            assign p_out[i + 1] = p_in[i + 1];
            assign p_out[i + 2] = p_in[i + 2];
            assign p_out[i + 3] = p_in[i + 3];
            assign p_out[i + 4] = p_in[i + 4];
            assign p_out[i + 5] = p_in[i + 5];
            assign p_out[i + 6] = p_in[i + 6];
            assign p_out[i + 7] = p_in[i + 7];
        end
    endgenerate
    assign generate_out = g_out;
    assign propogate_out = p_out;
endmodule