int cmd_line(int argv, char* argc[], const char** filenameInstr, const char** filenameData, char* cmode, char* mode, int* ni)
{
    if(argv == 1){
        if(filenameInstr != nullptr) *filenameInstr = "../../translator/out.bin";
        if(filenameData != nullptr) *filenameData= "data.bin";
        if(cmode != nullptr) *cmode = 'r';
        *ni = 100;
    }
    else if(argv == 2){
        if(argc[1][0] == '-'){
            *filenameInstr = "../../translator/out.bin";
            *filenameData= "data.bin";
            *cmode = argc[1][1];
            *mode = argc[1][2];
            *ni = 100;
        }
        else{
            *filenameInstr = argc[1];
            *filenameData= "data.bin";
            *cmode = 'r';
            *mode = 'a';
            *ni = 100;
        }
    }
    else if(argv == 3){
        if(argc[1][0] == '-'){
            *filenameInstr = argc[2];
            *filenameData= "data.bin";
            *cmode = argc[1][1];
            *mode = 'a';
            *ni = 100;
        }
        else{
            *filenameInstr = argc[1];
            *filenameData= argc[2];
            *cmode = 'r';
            *mode = 'a';
            *ni = 100;
        }
    }
    else if(argv == 4){
        if(argc[1][0] == '-'){
            *filenameInstr = argc[2];
            *filenameData= argc[3];
            *cmode = argc[1][1];
            *mode = argc[1][2];
            *ni = 100;
        }
        else{
            *filenameInstr = argc[1];
            *filenameData= argc[2];
            *cmode = 'r';
            *mode = 'a';
            *ni = 100;
        }
    }
    return 0;
}