#include "../include/main.h"
#include <signal.h>
// #include <signal/signal-dfs.h>
// #include <signal/sigaction.h>

struct sigaction sa;
int is_bg(str argv)
{
    if(argv[strlen(argv) -1] == '&') return 1;
    return 0;
}
void child_exited(int signal) {
  // This function is called when the child process exits
  printf("Child process is over\n");
}

void childHandler(int signal) {
    int status;
    int pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) 
    {
        if (WIFEXITED(status)) 
        {
            printf("Child with process id %d exitted normally\n", pid);
            bgarr[bgc].normal = 1;
        }
        else if(WIFSIGNALED(status)){
            bgarr[bgc].normal = 0;
        }
        bgarr[bgc].isover = 1;
    }

}

void go_bg(str cmd){
    char del[] = " \n\v\r\f";
    str cmd_dup = (str) malloc(strlen(cmd)*sizeof(char)); str token;
    strcpy(cmd_dup, cmd);
    str argv[MAX_INPUT_LENGTH]; int argc;
    token = strtok(cmd_dup, del);
    while(token != NULL){
      argv[argc++] = token;
      // printf("%s\n", argv[argc-1]);
      token = strtok(NULL, del);
    }
    argv[argc - 1] = NULL; // remove the '&'
    argc--;
    // for(int i=0; i<argc; i++) printf("%s \n", argv[i]);
    int status = 0;
    sa.sa_handler = childHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
            perror("Signal handler registration failed");
            exit(EXIT_FAILURE);
    }
    pid_t pid = fork();

    if(pid == 0){

        pid_t childpid = getpid();
        printf("\n[1] \t\t %d \n", childpid);
        
        if(execvp(*argv, argv) < 0)
        {
            printf("%s: command not found\n", *argv);
            fflush(stdout);
            exit(EXIT_FAILURE); 
        }
    }
    else{
        bgarr[bgc].pid = pid;
        strcpy(bgarr[bgc].command, *argv);
        bgarr[bgc].isover = 0;
        bgarr[bgc].printed = 0;
        bgarr[bgc].normal = 0;
        bgc++;
    }

}
