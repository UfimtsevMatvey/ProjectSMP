`include "../define/main.def.v"

function [LEN_DATA - 1:0] byte_swap(input wire [LEN_DATA - 1:0] word);
    begin
        byte_swap[7:0]      = word[63:56];
        byte_swap[15:8]     = word[55:48];
        byte_swap[23:16]    = word[47:40];
        byte_swap[31:24]    = word[39:32];
        byte_swap[39:32]    = word[31:24];
        byte_swap[47:40]    = word[23:16];
        byte_swap[55:48]    = word[15:8];
        byte_swap[63:56]    = word[7:0];
    end
endfunction