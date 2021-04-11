`include "../define/main.def.v"
module shift(
    input wire rst,
    input wire [LEN_DATA - 1:0] a,
    input wire [5:0] c,
    input wire [2:0] code,
    input wire carry,
    output wire [LEN_DATA - 1:0] s_res,
    output wire carry_out,
    output wire rst
)
always @(*) begin
    case (code)
        0 : begin //LSL
            case (c)
                0 :     begin s_res = a; end
                1 :     begin s_res = a << 1; end
                2 :     begin s_res = a << 2; end
                3 :     begin s_res = a << 3; end
                4 :     begin s_res = a << 4; end
                5 :     begin s_res = a << 5; end
                6 :     begin s_res = a << 6; end
                7 :     begin s_res = a << 7; end
                8 :     begin s_res = a << 8; end
                9 :     begin s_res = a << 9; end
                10 :    begin s_res = a << 10; end
                11 :    begin s_res = a << 11; end
                12 :    begin s_res = a << 12; end
                13 :    begin s_res = a << 13; end
                14 :    begin s_res = a << 14; end
                15 :    begin s_res = a << 15; end
                16 :    begin s_res = a << 16; end
                17 :    begin s_res = a << 17; end
                18 :    begin s_res = a << 18; end
                19 :    begin s_res = a << 19; end
                20 :    begin s_res = a << 20; end
                21 :    begin s_res = a << 21; end
                22 :    begin s_res = a << 22; end
                23 :    begin s_res = a << 23; end
                24 :    begin s_res = a << 24; end
                25 :    begin s_res = a << 25; end
                26 :    begin s_res = a << 26; end
                27 :    begin s_res = a << 27; end
                28 :    begin s_res = a << 28; end
                29 :    begin s_res = a << 29; end
                30 :    begin s_res = a << 30; end
                31 :    begin s_res = a << 31; end
                32 :    begin s_res = a << 32; end
                33 :    begin s_res = a << 33; end
                34 :    begin s_res = a << 34; end
                35 :    begin s_res = a << 35; end
                36 :    begin s_res = a << 36; end
                37 :    begin s_res = a << 37; end
                38 :    begin s_res = a << 38; end
                39 :    begin s_res = a << 39; end
                40 :    begin s_res = a << 40; end
                41 :    begin s_res = a << 41; end
                42 :    begin s_res = a << 42; end
                43 :    begin s_res = a << 43; end
                44 :    begin s_res = a << 44; end
                45 :    begin s_res = a << 45; end
                46 :    begin s_res = a << 46; end
                47 :    begin s_res = a << 47; end
                48 :    begin s_res = a << 48; end
                49 :    begin s_res = a << 49; end
                50 :    begin s_res = a << 50; end
                51 :    begin s_res = a << 51; end
                52 :    begin s_res = a << 52; end
                53 :    begin s_res = a << 53; end
                54 :    begin s_res = a << 54; end
                55 :    begin s_res = a << 55; end
                56 :    begin s_res = a << 56; end
                57 :    begin s_res = a << 57; end
                58 :    begin s_res = a << 58; end
                59 :    begin s_res = a << 59; end
                60 :    begin s_res = a << 60; end
                61 :    begin s_res = a << 61; end
                62 :    begin s_res = a << 62; end
                63 :    begin s_res = a << 63; end
            endcase
        end
        1 : begin //LSR
            case (c)
                0 :     begin s_res = a; end
                1 :     begin s_res = a >> 1; end
                2 :     begin s_res = a >> 2; end
                3 :     begin s_res = a >> 3; end
                4 :     begin s_res = a >> 4; end
                5 :     begin s_res = a >> 5; end
                6 :     begin s_res = a >> 6; end
                7 :     begin s_res = a >> 7; end
                8 :     begin s_res = a >> 8; end
                9 :     begin s_res = a >> 9; end
                10 :    begin s_res = a >> 10; end
                11 :    begin s_res = a >> 11; end
                12 :    begin s_res = a >> 12; end
                13 :    begin s_res = a >> 13; end
                14 :    begin s_res = a >> 14; end
                15 :    begin s_res = a >> 15; end
                16 :    begin s_res = a >> 16; end
                17 :    begin s_res = a >> 17; end
                18 :    begin s_res = a >> 18; end
                19 :    begin s_res = a >> 19; end
                20 :    begin s_res = a >> 20; end
                21 :    begin s_res = a >> 21; end
                22 :    begin s_res = a >> 22; end
                23 :    begin s_res = a >> 23; end
                24 :    begin s_res = a >> 24; end
                25 :    begin s_res = a >> 25; end
                26 :    begin s_res = a >> 26; end
                27 :    begin s_res = a >> 27; end
                28 :    begin s_res = a >> 28; end
                29 :    begin s_res = a >> 29; end
                30 :    begin s_res = a >> 30; end
                31 :    begin s_res = a >> 31; end
                32 :    begin s_res = a >> 32; end
                33 :    begin s_res = a >> 33; end
                34 :    begin s_res = a >> 34; end
                35 :    begin s_res = a >> 35; end
                36 :    begin s_res = a >> 36; end
                37 :    begin s_res = a >> 37; end
                38 :    begin s_res = a >> 38; end
                39 :    begin s_res = a >> 39; end
                40 :    begin s_res = a >> 40; end
                41 :    begin s_res = a >> 41; end
                42 :    begin s_res = a >> 42; end
                43 :    begin s_res = a >> 43; end
                44 :    begin s_res = a >> 44; end
                45 :    begin s_res = a >> 45; end
                46 :    begin s_res = a >> 46; end
                47 :    begin s_res = a >> 47; end
                48 :    begin s_res = a >> 48; end
                49 :    begin s_res = a >> 49; end
                50 :    begin s_res = a >> 50; end
                51 :    begin s_res = a >> 51; end
                52 :    begin s_res = a >> 52; end
                53 :    begin s_res = a >> 53; end
                54 :    begin s_res = a >> 54; end
                55 :    begin s_res = a >> 55; end
                56 :    begin s_res = a >> 56; end
                57 :    begin s_res = a >> 57; end
                58 :    begin s_res = a >> 58; end
                59 :    begin s_res = a >> 59; end
                60 :    begin s_res = a >> 60; end
                61 :    begin s_res = a >> 61; end
                62 :    begin s_res = a >> 62; end
                63 :    begin s_res = a >> 63; end
            endcase
        end
        2 : begin //ASR
            case (c) 
                0 :     begin s_res = a; end
                1 :     begin s_res = a >> 1; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 1] = {1{carry}}; end
                2 :     begin s_res = a >> 2; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 2] = {2{carry}}; end
                3 :     begin s_res = a >> 3; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 3] = {3{carry}}; end
                4 :     begin s_res = a >> 4; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 4] = {4{carry}}; end
                5 :     begin s_res = a >> 5; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 5] = {5{carry}}; end
                6 :     begin s_res = a >> 6; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 6] = {6{carry}}; end
                7 :     begin s_res = a >> 7; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 7] = {7{carry}}; end
                8 :     begin s_res = a >> 8; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 8] = {8{carry}}; end
                9 :     begin s_res = a >> 9; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 9] = {9{carry}}; end
                10 :    begin s_res = a >> 10; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 10] = {10{carry}}; end
                11 :    begin s_res = a >> 11; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 11] = {11{carry}}; end
                12 :    begin s_res = a >> 12; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 12] = {12{carry}}; end
                13 :    begin s_res = a >> 13; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 13] = {13{carry}}; end
                14 :    begin s_res = a >> 14; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 14] = {14{carry}}; end
                15 :    begin s_res = a >> 15; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 15] = {15{carry}}; end
                16 :    begin s_res = a >> 16; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 16] = {16{carry}}; end
                17 :    begin s_res = a >> 17; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 17] = {17{carry}}; end
                18 :    begin s_res = a >> 18; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 18] = {18{carry}}; end
                19 :    begin s_res = a >> 19; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 19] = {19{carry}}; end
                20 :    begin s_res = a >> 20; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 20] = {20{carry}}; end
                21 :    begin s_res = a >> 21; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 21] = {21{carry}}; end
                22 :    begin s_res = a >> 22; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 22] = {22{carry}}; end
                23 :    begin s_res = a >> 23; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 23] = {23{carry}}; end
                24 :    begin s_res = a >> 24; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 24] = {24{carry}}; end
                25 :    begin s_res = a >> 25; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 25] = {25{carry}}; end
                26 :    begin s_res = a >> 26; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 26] = {26{carry}}; end
                27 :    begin s_res = a >> 27; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 27] = {27{carry}}; end
                28 :    begin s_res = a >> 28; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 28] = {28{carry}}; end
                29 :    begin s_res = a >> 29; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 29] = {29{carry}}; end
                30 :    begin s_res = a >> 30; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 30] = {30{carry}}; end
                31 :    begin s_res = a >> 31; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 31] = {31{carry}}; end
                32 :    begin s_res = a >> 32; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 32] = {32{carry}}; end
                33 :    begin s_res = a >> 33; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 33] = {33{carry}}; end
                34 :    begin s_res = a >> 34; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 34] = {34{carry}}; end
                35 :    begin s_res = a >> 35; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 35] = {35{carry}}; end
                36 :    begin s_res = a >> 36; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 36] = {36{carry}}; end
                37 :    begin s_res = a >> 37; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 37] = {37{carry}}; end
                38 :    begin s_res = a >> 38; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 38] = {38{carry}}; end
                39 :    begin s_res = a >> 39; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 39] = {39{carry}}; end
                40 :    begin s_res = a >> 40; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 40] = {40{carry}}; end
                41 :    begin s_res = a >> 41; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 41] = {41{carry}}; end
                42 :    begin s_res = a >> 42; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 42] = {42{carry}}; end
                43 :    begin s_res = a >> 43; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 43] = {43{carry}}; end
                44 :    begin s_res = a >> 44; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 44] = {44{carry}}; end
                45 :    begin s_res = a >> 45; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 45] = {45{carry}}; end
                46 :    begin s_res = a >> 46; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 46] = {46{carry}}; end
                47 :    begin s_res = a >> 47; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 47] = {47{carry}}; end
                48 :    begin s_res = a >> 48; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 48] = {48{carry}}; end
                49 :    begin s_res = a >> 49; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 49] = {49{carry}}; end
                50 :    begin s_res = a >> 50; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 50] = {50{carry}}; end
                51 :    begin s_res = a >> 51; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 51] = {51{carry}}; end
                52 :    begin s_res = a >> 52; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 52] = {52{carry}}; end
                53 :    begin s_res = a >> 53; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 53] = {52{carry}}; end
                54 :    begin s_res = a >> 54; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 54] = {53{carry}}; end
                55 :    begin s_res = a >> 55; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 55] = {54{carry}}; end
                56 :    begin s_res = a >> 56; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 56] = {55{carry}}; end
                57 :    begin s_res = a >> 57; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 57] = {57{carry}}; end
                58 :    begin s_res = a >> 58; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 58] = {58{carry}}; end
                59 :    begin s_res = a >> 59; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 59] = {59{carry}}; end
                60 :    begin s_res = a >> 60; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 60] = {60{carry}}; end
                61 :    begin s_res = a >> 61; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 61] = {61{carry}}; end
                62 :    begin s_res = a >> 62; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 62] = {62{carry}}; end
                63 :    begin s_res = a >> 63; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 63] = {63{carry}}; end
            endcase
        end
        3 : begin //RRX
            case (c)
                0 :     begin {s_res, carry_out} = {a, carry}; end
                1 :     begin {s_res, carry_out} = {a, carry}>> 1; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 1] = a[LEN_DATA - 1 : LEN_DATA - 1 - 1]; end
                2 :     begin {s_res, carry_out} = {a, carry}>> 2; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 2] = a[LEN_DATA - 1 : LEN_DATA - 1 - 2]; end
                3 :     begin {s_res, carry_out} = {a, carry}>> 3; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 3] = a[LEN_DATA - 1 : LEN_DATA - 1 - 3]; end
                4 :     begin {s_res, carry_out} = {a, carry}>> 4; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 4] = a[LEN_DATA - 1 : LEN_DATA - 1 - 4]; end
                5 :     begin {s_res, carry_out} = {a, carry}>> 5; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 5] = a[LEN_DATA - 1 : LEN_DATA - 1 - 5]; end
                6 :     begin {s_res, carry_out} = {a, carry}>> 6; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 6] = a[LEN_DATA - 1 : LEN_DATA - 1 - 6]; end
                7 :     begin {s_res, carry_out} = {a, carry}>> 7; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 7] = a[LEN_DATA - 1 : LEN_DATA - 1 - 7]; end
                8 :     begin {s_res, carry_out} = {a, carry}>> 8; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 8] = a[LEN_DATA - 1 : LEN_DATA - 1 - 8]; end
                9 :     begin {s_res, carry_out} = {a, carry}>> 9; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 9] = a[LEN_DATA - 1 : LEN_DATA - 1 - 9]; end
                10 :    begin {s_res, carry_out} = {a, carry}>> 10; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 10] = a[LEN_DATA - 1 : LEN_DATA - 1 - 10]; end
                11 :    begin {s_res, carry_out} = {a, carry}>> 11; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 11] = a[LEN_DATA - 1 : LEN_DATA - 1 - 11]; end
                12 :    begin {s_res, carry_out} = {a, carry}>> 12; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 12] = a[LEN_DATA - 1 : LEN_DATA - 1 - 12]; end
                13 :    begin {s_res, carry_out} = {a, carry}>> 13; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 13] = a[LEN_DATA - 1 : LEN_DATA - 1 - 13]; end
                14 :    begin {s_res, carry_out} = {a, carry}>> 14; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 14] = a[LEN_DATA - 1 : LEN_DATA - 1 - 14]; end
                15 :    begin {s_res, carry_out} = {a, carry}>> 15; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 15] = a[LEN_DATA - 1 : LEN_DATA - 1 - 15]; end
                16 :    begin {s_res, carry_out} = {a, carry}>> 16; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 16] = a[LEN_DATA - 1 : LEN_DATA - 1 - 16]; end
                17 :    begin {s_res, carry_out} = {a, carry}>> 17; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 17] = a[LEN_DATA - 1 : LEN_DATA - 1 - 17]; end
                18 :    begin {s_res, carry_out} = {a, carry}>> 18; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 18] = a[LEN_DATA - 1 : LEN_DATA - 1 - 18]; end
                19 :    begin {s_res, carry_out} = {a, carry}>> 19; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 19] = a[LEN_DATA - 1 : LEN_DATA - 1 - 19]; end
                20 :    begin {s_res, carry_out} = {a, carry}>> 20; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 10] = a[LEN_DATA - 1 : LEN_DATA - 1 - 20]; end
                21 :    begin {s_res, carry_out} = {a, carry}>> 21; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 21] = a[LEN_DATA - 1 : LEN_DATA - 1 - 21]; end
                22 :    begin {s_res, carry_out} = {a, carry}>> 22; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 22] = a[LEN_DATA - 1 : LEN_DATA - 1 - 22]; end
                23 :    begin {s_res, carry_out} = {a, carry}>> 23; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 23] = a[LEN_DATA - 1 : LEN_DATA - 1 - 33]; end
                24 :    begin {s_res, carry_out} = {a, carry}>> 24; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 24] = a[LEN_DATA - 1 : LEN_DATA - 1 - 34]; end
                25 :    begin {s_res, carry_out} = {a, carry}>> 25; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 25] = a[LEN_DATA - 1 : LEN_DATA - 1 - 35]; end
                26 :    begin {s_res, carry_out} = {a, carry}>> 26; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 26] = a[LEN_DATA - 1 : LEN_DATA - 1 - 36]; end
                27 :    begin {s_res, carry_out} = {a, carry}>> 27; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 27] = a[LEN_DATA - 1 : LEN_DATA - 1 - 37]; end
                28 :    begin {s_res, carry_out} = {a, carry}>> 28; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 28] = a[LEN_DATA - 1 : LEN_DATA - 1 - 38]; end
                29 :    begin {s_res, carry_out} = {a, carry}>> 29; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 29] = a[LEN_DATA - 1 : LEN_DATA - 1 - 29]; end
                30 :    begin {s_res, carry_out} = {a, carry}>> 30; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 30] = a[LEN_DATA - 1 : LEN_DATA - 1 - 30]; end
                31 :    begin {s_res, carry_out} = {a, carry}>> 31; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 31] = a[LEN_DATA - 1 : LEN_DATA - 1 - 31]; end
                32 :    begin {s_res, carry_out} = {a, carry}>> 32; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 32] = a[LEN_DATA - 1 : LEN_DATA - 1 - 32]; end
                33 :    begin {s_res, carry_out} = {a, carry}>> 33; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 33] = a[LEN_DATA - 1 : LEN_DATA - 1 - 33]; end
                34 :    begin {s_res, carry_out} = {a, carry}>> 34; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 34] = a[LEN_DATA - 1 : LEN_DATA - 1 - 34]; end
                35 :    begin {s_res, carry_out} = {a, carry}>> 35; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 35] = a[LEN_DATA - 1 : LEN_DATA - 1 - 35]; end
                36 :    begin {s_res, carry_out} = {a, carry}>> 36; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 36] = a[LEN_DATA - 1 : LEN_DATA - 1 - 36]; end
                37 :    begin {s_res, carry_out} = {a, carry}>> 37; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 37] = a[LEN_DATA - 1 : LEN_DATA - 1 - 37]; end
                38 :    begin {s_res, carry_out} = {a, carry}>> 38; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 38] = a[LEN_DATA - 1 : LEN_DATA - 1 - 38]; end
                39 :    begin {s_res, carry_out} = {a, carry}>> 39; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 39] = a[LEN_DATA - 1 : LEN_DATA - 1 - 39]; end
                40 :    begin {s_res, carry_out} = {a, carry}>> 40; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 40] = a[LEN_DATA - 1 : LEN_DATA - 1 - 40]; end
                41 :    begin {s_res, carry_out} = {a, carry}>> 41; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 41] = a[LEN_DATA - 1 : LEN_DATA - 1 - 41]; end
                42 :    begin {s_res, carry_out} = {a, carry}>> 42; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 42] = a[LEN_DATA - 1 : LEN_DATA - 1 - 42]; end
                43 :    begin {s_res, carry_out} = {a, carry}>> 43; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 43] = a[LEN_DATA - 1 : LEN_DATA - 1 - 43]; end
                44 :    begin {s_res, carry_out} = {a, carry}>> 44; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 44] = a[LEN_DATA - 1 : LEN_DATA - 1 - 44]; end
                45 :    begin {s_res, carry_out} = {a, carry}>> 45; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 45] = a[LEN_DATA - 1 : LEN_DATA - 1 - 45]; end
                46 :    begin {s_res, carry_out} = {a, carry}>> 46; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 46] = a[LEN_DATA - 1 : LEN_DATA - 1 - 46]; end
                47 :    begin {s_res, carry_out} = {a, carry}>> 47; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 47] = a[LEN_DATA - 1 : LEN_DATA - 1 - 47]; end
                48 :    begin {s_res, carry_out} = {a, carry}>> 48; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 48] = a[LEN_DATA - 1 : LEN_DATA - 1 - 48]; end
                49 :    begin {s_res, carry_out} = {a, carry}>> 49; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 49] = a[LEN_DATA - 1 : LEN_DATA - 1 - 49]; end
                50 :    begin {s_res, carry_out} = {a, carry}>> 50; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 50] = a[LEN_DATA - 1 : LEN_DATA - 1 - 50]; end
                51 :    begin {s_res, carry_out} = {a, carry}>> 51; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 51] = a[LEN_DATA - 1 : LEN_DATA - 1 - 51]; end
                52 :    begin {s_res, carry_out} = {a, carry}>> 52; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 52] = a[LEN_DATA - 1 : LEN_DATA - 1 - 52]; end
                53 :    begin {s_res, carry_out} = {a, carry}>> 53; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 53] = a[LEN_DATA - 1 : LEN_DATA - 1 - 53]; end
                54 :    begin {s_res, carry_out} = {a, carry}>> 54; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 54] = a[LEN_DATA - 1 : LEN_DATA - 1 - 54]; end
                55 :    begin {s_res, carry_out} = {a, carry}>> 55; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 55] = a[LEN_DATA - 1 : LEN_DATA - 1 - 55]; end
                56 :    begin {s_res, carry_out} = {a, carry}>> 56; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 56] = a[LEN_DATA - 1 : LEN_DATA - 1 - 56]; end
                57 :    begin {s_res, carry_out} = {a, carry}>> 57; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 57] = a[LEN_DATA - 1 : LEN_DATA - 1 - 57]; end
                58 :    begin {s_res, carry_out} = {a, carry}>> 58; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 58] = a[LEN_DATA - 1 : LEN_DATA - 1 - 58]; end
                59 :    begin {s_res, carry_out} = {a, carry}>> 59; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 59] = a[LEN_DATA - 1 : LEN_DATA - 1 - 59]; end
                60 :    begin {s_res, carry_out} = {a, carry}>> 60; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 60] = a[LEN_DATA - 1 : LEN_DATA - 1 - 60]; end
                61 :    begin {s_res, carry_out} = {a, carry}>> 61; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 61] = a[LEN_DATA - 1 : LEN_DATA - 1 - 61]; end
                62 :    begin {s_res, carry_out} = {a, carry}>> 62; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 62] = a[LEN_DATA - 1 : LEN_DATA - 1 - 62]; end
                63 :    begin {s_res, carry_out} = {a, carry}>> 63; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 63] = a[LEN_DATA - 1 : LEN_DATA - 1 - 63]; end
            endcase
        end
        4 : begin            
            case (c)
                0 :     begin s_res = a; end
                1 :     begin s_res = a>> 1; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 1] = a[LEN_DATA - 1 : LEN_DATA - 1 - 1]; end
                2 :     begin s_res = a>> 2; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 2] = a[LEN_DATA - 1 : LEN_DATA - 1 - 2]; end
                3 :     begin s_res = a>> 3; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 3] = a[LEN_DATA - 1 : LEN_DATA - 1 - 3]; end
                4 :     begin s_res = a>> 4; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 4] = a[LEN_DATA - 1 : LEN_DATA - 1 - 4]; end
                5 :     begin s_res = a>> 5; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 5] = a[LEN_DATA - 1 : LEN_DATA - 1 - 5]; end
                6 :     begin s_res = a>> 6; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 6] = a[LEN_DATA - 1 : LEN_DATA - 1 - 6]; end
                7 :     begin s_res = a>> 7; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 7] = a[LEN_DATA - 1 : LEN_DATA - 1 - 7]; end
                8 :     begin s_res = a>> 8; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 8] = a[LEN_DATA - 1 : LEN_DATA - 1 - 8]; end
                9 :     begin s_res = a>> 9; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 9] = a[LEN_DATA - 1 : LEN_DATA - 1 - 9]; end
                10 :    begin s_res = a>> 10; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 10] = a[LEN_DATA - 1 : LEN_DATA - 1 - 10]; end
                11 :    begin s_res = a>> 11; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 11] = a[LEN_DATA - 1 : LEN_DATA - 1 - 11]; end
                12 :    begin s_res = a>> 12; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 12] = a[LEN_DATA - 1 : LEN_DATA - 1 - 12]; end
                13 :    begin s_res = a>> 13; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 13] = a[LEN_DATA - 1 : LEN_DATA - 1 - 13]; end
                14 :    begin s_res = a>> 14; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 14] = a[LEN_DATA - 1 : LEN_DATA - 1 - 14]; end
                15 :    begin s_res = a>> 15; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 15] = a[LEN_DATA - 1 : LEN_DATA - 1 - 15]; end
                16 :    begin s_res = a>> 16; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 16] = a[LEN_DATA - 1 : LEN_DATA - 1 - 16]; end
                17 :    begin s_res = a>> 17; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 17] = a[LEN_DATA - 1 : LEN_DATA - 1 - 17]; end
                18 :    begin s_res = a>> 18; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 18] = a[LEN_DATA - 1 : LEN_DATA - 1 - 18]; end
                19 :    begin s_res = a>> 19; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 19] = a[LEN_DATA - 1 : LEN_DATA - 1 - 19]; end
                20 :    begin s_res = a>> 20; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 10] = a[LEN_DATA - 1 : LEN_DATA - 1 - 20]; end
                21 :    begin s_res = a>> 21; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 21] = a[LEN_DATA - 1 : LEN_DATA - 1 - 21]; end
                22 :    begin s_res = a>> 22; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 22] = a[LEN_DATA - 1 : LEN_DATA - 1 - 22]; end
                23 :    begin s_res = a>> 23; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 23] = a[LEN_DATA - 1 : LEN_DATA - 1 - 33]; end
                24 :    begin s_res = a>> 24; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 24] = a[LEN_DATA - 1 : LEN_DATA - 1 - 34]; end
                25 :    begin s_res = a>> 25; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 25] = a[LEN_DATA - 1 : LEN_DATA - 1 - 35]; end
                26 :    begin s_res = a>> 26; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 26] = a[LEN_DATA - 1 : LEN_DATA - 1 - 36]; end
                27 :    begin s_res = a>> 27; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 27] = a[LEN_DATA - 1 : LEN_DATA - 1 - 37]; end
                28 :    begin s_res = a>> 28; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 28] = a[LEN_DATA - 1 : LEN_DATA - 1 - 38]; end
                29 :    begin s_res = a>> 29; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 29] = a[LEN_DATA - 1 : LEN_DATA - 1 - 29]; end
                30 :    begin s_res = a>> 30; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 30] = a[LEN_DATA - 1 : LEN_DATA - 1 - 30]; end
                31 :    begin s_res = a>> 31; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 31] = a[LEN_DATA - 1 : LEN_DATA - 1 - 31]; end
                32 :    begin s_res = a>> 32; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 32] = a[LEN_DATA - 1 : LEN_DATA - 1 - 32]; end
                33 :    begin s_res = a>> 33; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 33] = a[LEN_DATA - 1 : LEN_DATA - 1 - 33]; end
                34 :    begin s_res = a>> 34; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 34] = a[LEN_DATA - 1 : LEN_DATA - 1 - 34]; end
                35 :    begin s_res = a>> 35; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 35] = a[LEN_DATA - 1 : LEN_DATA - 1 - 35]; end
                36 :    begin s_res = a>> 36; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 36] = a[LEN_DATA - 1 : LEN_DATA - 1 - 36]; end
                37 :    begin s_res = a>> 37; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 37] = a[LEN_DATA - 1 : LEN_DATA - 1 - 37]; end
                38 :    begin s_res = a>> 38; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 38] = a[LEN_DATA - 1 : LEN_DATA - 1 - 38]; end
                39 :    begin s_res = a>> 39; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 39] = a[LEN_DATA - 1 : LEN_DATA - 1 - 39]; end
                40 :    begin s_res = a>> 40; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 40] = a[LEN_DATA - 1 : LEN_DATA - 1 - 40]; end
                41 :    begin s_res = a>> 41; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 41] = a[LEN_DATA - 1 : LEN_DATA - 1 - 41]; end
                42 :    begin s_res = a>> 42; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 42] = a[LEN_DATA - 1 : LEN_DATA - 1 - 42]; end
                43 :    begin s_res = a>> 43; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 43] = a[LEN_DATA - 1 : LEN_DATA - 1 - 43]; end
                44 :    begin s_res = a>> 44; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 44] = a[LEN_DATA - 1 : LEN_DATA - 1 - 44]; end
                45 :    begin s_res = a>> 45; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 45] = a[LEN_DATA - 1 : LEN_DATA - 1 - 45]; end
                46 :    begin s_res = a>> 46; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 46] = a[LEN_DATA - 1 : LEN_DATA - 1 - 46]; end
                47 :    begin s_res = a>> 47; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 47] = a[LEN_DATA - 1 : LEN_DATA - 1 - 47]; end
                48 :    begin s_res = a>> 48; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 48] = a[LEN_DATA - 1 : LEN_DATA - 1 - 48]; end
                49 :    begin s_res = a>> 49; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 49] = a[LEN_DATA - 1 : LEN_DATA - 1 - 49]; end
                50 :    begin s_res = a>> 50; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 50] = a[LEN_DATA - 1 : LEN_DATA - 1 - 50]; end
                51 :    begin s_res = a>> 51; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 51] = a[LEN_DATA - 1 : LEN_DATA - 1 - 51]; end
                52 :    begin s_res = a>> 52; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 52] = a[LEN_DATA - 1 : LEN_DATA - 1 - 52]; end
                53 :    begin s_res = a>> 53; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 53] = a[LEN_DATA - 1 : LEN_DATA - 1 - 53]; end
                54 :    begin s_res = a>> 54; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 54] = a[LEN_DATA - 1 : LEN_DATA - 1 - 54]; end
                55 :    begin s_res = a>> 55; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 55] = a[LEN_DATA - 1 : LEN_DATA - 1 - 55]; end
                56 :    begin s_res = a>> 56; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 56] = a[LEN_DATA - 1 : LEN_DATA - 1 - 56]; end
                57 :    begin s_res = a>> 57; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 57] = a[LEN_DATA - 1 : LEN_DATA - 1 - 57]; end
                58 :    begin s_res = a>> 58; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 58] = a[LEN_DATA - 1 : LEN_DATA - 1 - 58]; end
                59 :    begin s_res = a>> 59; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 59] = a[LEN_DATA - 1 : LEN_DATA - 1 - 59]; end
                60 :    begin s_res = a>> 60; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 60] = a[LEN_DATA - 1 : LEN_DATA - 1 - 60]; end
                61 :    begin s_res = a>> 61; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 61] = a[LEN_DATA - 1 : LEN_DATA - 1 - 61]; end
                62 :    begin s_res = a>> 62; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 62] = a[LEN_DATA - 1 : LEN_DATA - 1 - 62]; end
                63 :    begin s_res = a>> 63; s_res[LEN_DATA - 1 : LEN_DATA - 1 - 63] = a[LEN_DATA - 1 : LEN_DATA - 1 - 63]; end
            endcase
        end
        default : begin
            s_res = {64{1'b0}};
        end
    endcase
end
endmodule