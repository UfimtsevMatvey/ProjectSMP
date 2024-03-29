`include "../../define/main.def.v"

module adder_stage6(
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
        for (i = 16; i < `LEN_DATA + 1; i = i + 32) begin : stage6_16odd
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
            gp_cell gpcell8(
                .g_left (g_in   [i + 8] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 8] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 8] ),
                .p_out  (p_out  [i + 8] )
            );
            gp_cell gpcell9(
                .g_left (g_in   [i + 9] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 9] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 9] ),
                .p_out  (p_out  [i + 9] )
            );
            gp_cell gpcell10(
                .g_left (g_in   [i + 10]),
                .g_right(g_in   [i - 1]),
                .p_left (p_in   [i + 10]),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 10]),
                .p_out  (p_out  [i + 10])
            );
            gp_cell gpcell11(
                .g_left (g_in   [i + 11] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 11] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 11] ),
                .p_out  (p_out  [i + 11] )
            );
            gp_cell gpcell12(
                .g_left (g_in   [i + 12] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 12] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 12] ),
                .p_out  (p_out  [i + 12] )
            );
            gp_cell gpcell13(
                .g_left (g_in   [i + 13] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 13] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 13] ),
                .p_out  (p_out  [i + 13] )
            );
            gp_cell gpcell14(
                .g_left (g_in   [i + 14] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 14] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 14] ),
                .p_out  (p_out  [i + 14] )
            );
            gp_cell gpcell15(
                .g_left (g_in   [i + 15] ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i + 15] ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i + 15] ),
                .p_out  (p_out  [i + 15] )
            );
        end
       
        for (i = 0; i < `LEN_DATA; i = i + 32) begin : stage6_16ever
            assign g_out[i] = g_in[i];
            assign g_out[i + 1] = g_in[i + 1];
            assign g_out[i + 2] = g_in[i + 2];
            assign g_out[i + 3] = g_in[i + 3];
            assign g_out[i + 4] = g_in[i + 4];
            assign g_out[i + 5] = g_in[i + 5];
            assign g_out[i + 6] = g_in[i + 6];
            assign g_out[i + 7] = g_in[i + 7];
            assign g_out[i + 8] = g_in[i + 8];
            assign g_out[i + 9] = g_in[i + 9];
            assign g_out[i + 10] = g_in[i + 10];
            assign g_out[i + 11] = g_in[i + 11];
            assign g_out[i + 12] = g_in[i + 12];
            assign g_out[i + 13] = g_in[i + 13];
            assign g_out[i + 14] = g_in[i + 14];
            assign g_out[i + 15] = g_in[i + 15];
            assign p_out[i] = p_in[i];
            assign p_out[i + 1] = p_in[i + 1];
            assign p_out[i + 2] = p_in[i + 2];
            assign p_out[i + 3] = p_in[i + 3];
            assign p_out[i + 4] = p_in[i + 4];
            assign p_out[i + 5] = p_in[i + 5];
            assign p_out[i + 6] = p_in[i + 6];
            assign p_out[i + 7] = p_in[i + 7];
            assign p_out[i + 8] = p_in[i + 8];
            assign p_out[i + 9] = p_in[i + 9];
            assign p_out[i + 10] = p_in[i + 10];
            assign p_out[i + 11] = p_in[i + 11];
            assign p_out[i + 12] = p_in[i + 12];
            assign p_out[i + 13] = p_in[i + 13];
            assign p_out[i + 14] = p_in[i + 14];
            assign p_out[i + 15] = p_in[i + 15];
        end
        assign g_out[`LEN_DATA] = g_in[`LEN_DATA];
        assign p_out[`LEN_DATA] = p_in[`LEN_DATA];
    endgenerate
    assign generate_out = g_out & mask;
    assign propogate_out = p_out & mask;
endmodule