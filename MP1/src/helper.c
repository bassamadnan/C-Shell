// returns a string with replace
#include "../include/main.h"

str replace(str input, char prev, str curr)
{
    int n = (int)strlen(input), instances = 0;
    for (int i = 0; i < n; i++) if (input[i] == prev) instances++;
    str ans = calloc(n + instances + 5, sizeof(char));
    for(int i=0; i<n; i++){
        if(input[i] == prev) strcat(ans, curr);
        else strncat(ans,  &input[i], 1);
    }
    return ans;
}

// returns 1 if two strings are equal
bool cmp(str s1, str s2){
    return !strcmp(s1, s2);
}

bool cmpn(str s1, str s2, int n){
    for(int i=0; i<n; i++) if(s1[i] != s2[i]) return 0;
    return 1;
}

void green(str s)
{
    printf("\033[1;32m%s\033[0m\n", s);
}

void blue(str s)
{
    printf("\033[1;34m%s\033[0m\n", s);
}
void yellow(str s){
    printf("\033[1;33m%s\033[0m\n", s);
}
// https://man7.org/linux/man-pages/man7/inode.7.html
bool is_dir(mode_t mode){
    
    return S_ISDIR(mode);

}
bool is_exe(mode_t mode){
 
    return (mode & S_IXUSR);
}

bool is_reg(mode_t mode){

    return S_ISREG(mode);
}