#include "../include/main.h"

void foreground(str cmd){
    char del[] = " \n\v\r\f";
    // str cmd_dup = strdup(cmd);
    char cmd_dup[strlen(cmd)]; strcpy(cmd_dup, cmd);
    str token;
    str argv[MAX_INPUT_LENGTH]; int argc;
    // printf("Got here\n");
    token = strtok(cmd_dup, del);
    while(token != NULL){
      argv[argc++] = token;
      // printf("%s\n", argv[argc-1]);
      token = strtok(NULL, del);
    }
    argv[argc] = NULL;
    pid_t pid = fork(); // image process to execute execvp
    if(pid == 0){
      execvp(*argv, argv);
    }
     
}