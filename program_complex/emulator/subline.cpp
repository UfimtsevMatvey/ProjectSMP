#include <cstdlib>
bool subline(int argv, char* argc[], char* word)
{
    bool res = true;
    bool temp_res = true;
    for(int i = 1; i < argv; i = i + 1){
        temp_res = true;
        int j = 0;
        while ((word[j] != 0) || (argc[i][j] != 0)){
            temp_res = temp_res && (argc[i][j] == word[j]);
            j = j + 1;
        }
        res = res && temp_res;
    }
    return res;
}

//return 2 number, where index first non-parametric parameter cmd line
void non_param_cntr(int argv, char* argc[], char param_char, int* res0, int* res1)
{
    int t[2] = {0, 0};
    int non_cntr = 0;
    for(int i = 1; i < argv; i = i + 1){
        if(argc[i][0] != param_char){
            t[non_cntr] = i;
            non_cntr = non_cntr + 1;
            if(non_cntr == 2) break;
        }
    }
    *res0 = t[0];
    *res1 = t[1];
}

//return one number from massive string
int find_num(int argv, char* argc[])
{
    int res;
    bool temp_res = false;
    for(int i = 1; i < argv; i = i + 1){
        temp_res = true;
        int j = 0;
        while(argc[i][j] != 0){
            temp_res = temp_res && (argc[i][j] > '0' - 1 && argc[i][j] < '9' + 1);
            j = j + 1;
        }
        if(temp_res) {
            res = strtol(argc[i], nullptr, 10);
            break;
        }
    }
    return res;
}