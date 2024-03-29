`include "../../define/main.def.v"

module adder_stage4(
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
        for (i = 4; i < `LEN_DATA; i = i + 8) begin : stage4_4odd
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
        end
        for (i = 0; i < `LEN_DATA; i = i + 8) begin : stage4_4ever
            assign g_out[i    ] = g_in[i    ];
            assign g_out[i + 1] = g_in[i + 1];
            assign g_out[i + 2] = g_in[i + 2];
            assign g_out[i + 3] = g_in[i + 3];
            assign p_out[i    ] = p_in[i    ];
            assign p_out[i + 1] = p_in[i + 1];
            assign p_out[i + 2] = p_in[i + 2];
            assign p_out[i + 3] = p_in[i + 3];
        end
        assign g_out[`LEN_DATA] = g_in[`LEN_DATA];
        assign p_out[`LEN_DATA] = p_in[`LEN_DATA];
    endgenerate
    assign generate_out = g_out & mask;
    assign propogate_out = p_out & mask;
endmodule