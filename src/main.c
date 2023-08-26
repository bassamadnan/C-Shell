#include "../include/main.h"

struct bgjob bgarr[MAX_JOBS];
int bgc = 0;
int main(){
    while(1){
        printPrompt();
        str_arr cmds = input();
        print_bg();
        for(int i=0; cmds[i] != NULL; i++){

            int gobg = is_bg(cmds[i]);
            if(gobg){
                setpgid(0, 0);
                go_bg(cmds[i]);
            }
            else process(cmds[i]);
        }
    }
 
    return 0;
}