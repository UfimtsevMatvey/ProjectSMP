`include "../../define/main.def.v"

module adder_stage1(
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
        for (i = 1; i < `LEN_DATA; i = i + 1) begin : stage1
            gp_cell gpcell(
                .g_left (g_in   [i]     ),
                .g_right(g_in   [i - 1] ),
                .p_left (p_in   [i]     ),
                .p_right(p_in   [i - 1] ),
                .g_out  (g_out  [i]     ),
                .p_out  (p_out  [i] )
            );
        end
    endgenerate
    assign g_out[0] = g_in;
    assign p_out[0] = p_in;
    assign generate_out = g_out;
    assign propogate_out = p_out;
endmodule