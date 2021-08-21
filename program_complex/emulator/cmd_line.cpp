#include "headers/subline.h"

int cmd_line(int argv, char* argc[], const char** filenameInstr, const char** filenameData, char* cmode, char* mode, int* ni)
{
    int instr_i = 0;
    int data_i = 0;
    if((filenameInstr == nullptr) || (filenameData == nullptr) || (cmode == nullptr) || (mode == nullptr))
        return 1;

    char* pr = "-r";
    char* pd = "-d";
    char* ps = "-s";
    char* ph = "-h";
    char* pa = "-a";
    if(subline(argv, argc, pr)) {*cmode = 'r'; *mode = 0;}
    if(subline(argv, argc, pd)) {*cmode = 'd'; *mode = 0;}
    if(subline(argv, argc, ps)) {*cmode = 's'; *mode = 0;}
    if(subline(argv, argc, ph)) {*cmode = 0; *mode = 'h';}
    if(subline(argv, argc, pa)) {*cmode = 0; *mode = 'a';}
    
    non_param_cntr(argv, argc, '-', &instr_i, &data_i);

    if(instr_i != 0) 
        *filenameInstr = argc[instr_i];
    else 
        *filenameInstr = "../../translator/out.bin";
    
    if(data_i != 0)
        *filenameData = argc[data_i];
    else
        *filenameData = "data.bin";
    
    *ni = find_num(argv, argc);
    return 0;
}