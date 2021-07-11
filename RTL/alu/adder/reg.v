module register #(
    parameter width = 64
) (
    input wire rst_n,
    input wire clk, 
    input wire en,
    input wire [width - 1:0] d,
    output reg [width - 1:0] q 
);
    always @(posedge clk) begin
        if(~rst_n)    
            q <= 0;
        else if(en) 
            q <= d;
    end
endmodule