#include "main.h"
int main(){
    str_arr strarr = (char**)malloc(sizeof(char*)*2);
    strcpy(strarr[0], "Hi");
    printf("%s", strarr[0]);
    return 0;
}