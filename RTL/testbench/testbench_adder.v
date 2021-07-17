`include "../define/main.def.v"
`include "../define/alu.def.v"

`timescale 1ns/1ps
module testbench_adder();

    integer i = 0;
    integer j = 0;
    reg en;
    reg DUT_clk;
    reg DUT_hclk;
    reg DUT_rst_n;
    reg DUT_en;
    reg DUT_valid;
    reg [`LEN_DATA - 1:0] DUT_a;
    reg [`LEN_DATA - 1:0] DUT_b;
    reg [`LEN_DATA - 1:0] DUT_imm;
    reg [`LEN_DATA - 1:0] DUT_res;
    reg [`LEN_DATA - 1:0] DUT_ex_res;
    reg [`LEN_DATA - 1:0] DUT_res_dly;
    reg [`LEN_DATA - 1:0] DUT_res_dly_dly;
    reg [`LEN_DATA - 1:0] DUT_ex_res_dly;
    reg [`LEN_DATA - 1:0] DUT_ex_res_dly_dly;
    reg [`LEN_DATA - 1:0] res_pipeline [16:0];
    reg [`LEN_DATA - 1:0] ex_res_pipeline [16:0];
    reg [7:0] DUT_cin;
    reg [`LEN_TYPE_ALU - 1:0] DUT_code;
    reg [7:0] DUT_cmsk_n;
    wire [`LEN_DATA - 1:0] DUT_sum;
    wire [`LEN_DATA - 1:0] DUT_result;
    wire [`LEN_DATA - 1:0] DUT_ex_result;
    
    wire DUT_cout;
    wire DUT_rdy;
    always #1 DUT_clk = ~DUT_clk;
    always #2 DUT_hclk = ~DUT_hclk;

    function [`LEN_DATA - 1:0] byte_swap_test( input [`LEN_DATA - 1:0] word);
    begin
        byte_swap_test[7:0]      = word[63:56];
        byte_swap_test[15:8]     = word[55:48];
        byte_swap_test[23:16]    = word[47:40];
        byte_swap_test[31:24]    = word[39:32];
        byte_swap_test[39:32]    = word[31:24];
        byte_swap_test[47:40]    = word[23:16];
        byte_swap_test[55:48]    = word[15:8];
        byte_swap_test[63:56]    = word[7:0];
    end 
    endfunction 

    alu DUT_alu(
        .rst_n  (DUT_rst_n  ),
        .clk    (DUT_clk    ),
        .en     (DUT_en     ),
        .a      (DUT_a      ),
        .b      (DUT_b      ),      
        .imm    (DUT_imm    ),
        .cin    (DUT_cin    ),
        .code   (DUT_code   ),
        .result (DUT_result ),
        .ex_result(DUT_ex_result),
        .cout   (DUT_cout   ),
        .rdy    (DUT_rdy    )
    );
    initial begin
        en         = 1'b0;
        DUT_clk    = 1'b0;
        DUT_hclk   = 1'b0;
        DUT_rst_n  = 1'b0;
        DUT_en     = 1'b0;
        DUT_valid  = 1'b0;
        DUT_a      = {`LEN_DATA{1'b0}};
        DUT_b      = {`LEN_DATA{1'b0}};
        DUT_imm    = {`LEN_DATA{1'b0}};
        DUT_cin    = 8'b0;
        DUT_code   = 0;
        DUT_cmsk_n = 8'h00;
        #34
        DUT_code   = 5'b00001;
        en         = 1'b1;
        DUT_rst_n   = 1'b1;
        DUT_en     = 1'b1;
        #1000
        $finish;
    end
    always @(posedge DUT_hclk or negedge DUT_hclk) begin
        if(en) begin
            if(DUT_hclk) begin
                j <= j + 1;
                if(j%10 == 0)
                    DUT_code <= DUT_code + 5'b00001;
            end 
        end 
    end 
    always @(posedge DUT_hclk or negedge DUT_hclk) begin
        if(en) begin
            if(DUT_hclk) begin
                DUT_valid  <= 1'b1;
                DUT_a      <= {$random, $random};
                DUT_b      <= {$random, $random}; 
                DUT_imm    <= {$random, $random};
                DUT_cin    <= $random;
                DUT_cmsk_n <= $random;
                DUT_code   <= `ALU_ADD64;
                case (DUT_code)
                    `ALU_ADD64 : begin DUT_res = DUT_a + DUT_b; end
                    `ALU_ADC64 : begin DUT_res = DUT_a + DUT_b + DUT_cin[0]; end
                    `ALU_ADD32 : begin DUT_res = {DUT_a[63:32] + DUT_b[63:32], DUT_a[31:0 ] + DUT_b[31:0 ]}; end
                    `ALU_ADD16 : begin DUT_res = {DUT_a[63:48]+DUT_b[63:48],DUT_a[47:32]+DUT_b[47:32],DUT_a[31:16]+DUT_b[31:16],DUT_a[15:0]+DUT_b[15:0]}; end
                    `ALU_ADD8  : begin DUT_res = {DUT_a[63:56]+DUT_b[63:56],DUT_a[55:48]+DUT_b[55:48],DUT_a[47:40]+DUT_b[47:40],DUT_a[39:32]+DUT_b[39:32],
                        DUT_a[31:24]+DUT_b[31:24],DUT_a[23:16]+DUT_b[23:16],DUT_a[15:8]+DUT_b[15:8],DUT_a[7:0]+DUT_b[7:0]}; end
                    `ALU_SUB64 : begin DUT_res = DUT_a - DUT_b; end
                    `ALU_RSB64 : begin DUT_res =-DUT_a + DUT_b;end
                    `ALU_SBC64 : begin DUT_res = DUT_a - DUT_b + DUT_cin[0]; end
                    `ALU_SUB32 : begin DUT_res = {DUT_a[63:32] - DUT_b[63:32], DUT_a[31:0 ] - DUT_b[31:0 ]}; end
                    `ALU_SUB16 : begin DUT_res = {DUT_a[63:48]-DUT_b[63:48],DUT_a[47:32]-DUT_b[47:32],DUT_a[31:16]-DUT_b[31:16],DUT_a[15:0]-DUT_b[15:0]}; end
                    `ALU_SUB8  : begin DUT_res = {DUT_a[63:56]-DUT_b[63:56],DUT_a[55:48]-DUT_b[55:48],DUT_a[47:40]-DUT_b[47:40],DUT_a[39:32]-DUT_b[39:32],
                        DUT_a[31:24]-DUT_b[31:24],DUT_a[23:16]-DUT_b[23:16],DUT_a[15:8]-DUT_b[15:8],DUT_a[7:0]-DUT_b[7:0]}; end
                    `ALU_AND   : begin DUT_res = DUT_a & DUT_b;  end
                    `ALU_EOR   : begin DUT_res = DUT_a ^ DUT_b;  end
                    `ALU_ORR   : begin DUT_res = DUT_a | DUT_b;  end
                    `ALU_TST   : begin DUT_res = 64'b0;  end
                    `ALU_TEQ   : begin DUT_res = 64'b0;  end
                    `ALU_CMP   : begin DUT_res = 64'b0;  end
                    `ALU_CMN   : begin DUT_res = 64'b0;  end
                    `ALU_MVN   : begin DUT_res = ~DUT_a; end
                    `ALU_LSL   : begin DUT_res = DUT_a << DUT_b[5:0]; end
                    `ALU_LSR   : begin DUT_res = DUT_a >> DUT_b[5:0]; end
                    `ALU_ASR   : begin DUT_res = {DUT_cin[0],DUT_a} << DUT_b[5:0]; end
                    `ALU_RRX   : begin DUT_res = ({DUT_cin[0],DUT_a} >> DUT_b[5:0]) | ({DUT_cin[0],DUT_a} << (64 - DUT_b[5:0])); end
                    `ALU_ROR   : begin DUT_res = (DUT_a >> DUT_b[5:0]) | (DUT_a << (64 - DUT_b[5:0])); end
                    `ALU_BSWP  : begin DUT_res = byte_swap_test(DUT_a); end
                    `ALU_SWR   : begin DUT_res = DUT_b; DUT_ex_res = DUT_a; end
                    `ALU_ADD128_BYTE : begin 
                        DUT_res       = {DUT_imm[63:56]+DUT_a[63:56],DUT_imm[55:48]+DUT_a[55:48],DUT_imm[47:40]+DUT_a[47:40],DUT_imm[39:32]+DUT_a[39:32],
                            DUT_imm[31:24]+DUT_a[31:24],DUT_imm[23:16]+DUT_a[23:16],DUT_imm[15:8]+DUT_a[15:8],DUT_imm[7:0]+DUT_a[7:0]};
                        DUT_ex_res    = {DUT_b[63:56]+DUT_imm[63:56],DUT_b[55:48]+DUT_imm[55:48],DUT_b[47:40]+DUT_imm[47:40],DUT_b[39:32]+DUT_imm[39:32],
                            DUT_b[31:24]+DUT_imm[31:24],DUT_b[23:16]+DUT_imm[23:16],DUT_b[15:8]+DUT_imm[15:8],DUT_b[7:0]+DUT_imm[7:0]};
                    end
                    `ALU_SUB128_BYTE : begin 
                        DUT_res       = {-DUT_imm[63:56]+DUT_a[63:56],-DUT_imm[55:48]+DUT_a[55:48],-DUT_imm[47:40]+DUT_a[47:40],-DUT_imm[39:32]+DUT_a[39:32],
                            -DUT_imm[31:24]+DUT_a[31:24],-DUT_imm[23:16]+DUT_a[23:16],-DUT_imm[15:8]+DUT_a[15:8],-DUT_imm[7:0]+DUT_a[7:0]};
                        DUT_ex_res    = {DUT_b[63:56]-DUT_imm[63:56],DUT_b[55:48]-DUT_imm[55:48],DUT_b[47:40]-DUT_imm[47:40],DUT_b[39:32]-DUT_imm[39:32],
                            DUT_b[31:24]-DUT_imm[31:24],DUT_b[23:16]-DUT_imm[23:16],DUT_b[15:8]-DUT_imm[15:8],DUT_b[7:0]-DUT_imm[7:0]};
                    end
                    `ALU_ADD128_TWOBYTE : begin 
                        DUT_res       = {DUT_imm[63:48]+DUT_a[63:48],DUT_imm[47:32]+DUT_a[47:32],DUT_imm[31:16]+DUT_a[31:16],DUT_imm[15:0]+DUT_a[15:0]};
                        DUT_ex_res    = {DUT_imm[63:48]+DUT_b[63:48],DUT_imm[47:32]+DUT_b[47:32],DUT_imm[31:16]+DUT_b[31:16],DUT_imm[15:0]+DUT_b[15:0]};
                    end
                    `ALU_SUB128_TWOBYTE : begin 
                        DUT_res       = {-DUT_imm[63:48]+DUT_a[63:48],-DUT_imm[47:32]+DUT_a[47:32],-DUT_imm[31:16]+DUT_a[31:16],-DUT_imm[15:0]+DUT_a[15:0]};
                        DUT_ex_res    = {-DUT_imm[63:48]+DUT_b[63:48],-DUT_imm[47:32]+DUT_b[47:32],-DUT_imm[31:16]+DUT_b[31:16],-DUT_imm[15:0]+DUT_b[15:0]};
                    end
                endcase 
                res_pipeline[0]      <= DUT_res;
                ex_res_pipeline[0]   <= DUT_ex_res;
                for(i = 0; i < 16; i = i + 1) begin
                    res_pipeline[i + 1]    <= res_pipeline[i];
                    ex_res_pipeline[i + 1] <= ex_res_pipeline[i];
                end 
            end
            else begin
               DUT_valid  <= 1'b0; 
            end
        end
    end
    always @(posedge DUT_clk) begin
        DUT_res_dly_dly    <= res_pipeline[3];
        DUT_ex_res_dly_dly <= ex_res_pipeline[3];
        DUT_res_dly    <= DUT_res_dly_dly;
        DUT_ex_res_dly <= DUT_ex_res_dly_dly;
    end
endmodule