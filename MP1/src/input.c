#include "../include/main.h"
void process(str cmd){
    char del[] = " \n\v\r\f";
    str cmd_dup = (str) malloc(strlen(cmd)*sizeof(char)); str token;
    strcpy(cmd_dup, cmd);
    // printf("Got here\n");
    token = strtok(cmd, del);
    if(token != NULL){
        if(cmp(token, "exit") || cmp(token, "quit")){

            exit(0);
        }
        else if(cmp(token, "echo")){ // implemented here
            str words[BUFFER_SIZE];
            int argc = 0;
            // in bash, pressing 
            while((token = strtok(NULL, del)) != NULL){
                if(token[0] == '\"') strcpy(del, ""); // for handling double qutations stop checking anymore delims
                // assumption: does not check if it ends with ", 
                // it is assumed that the user enters echo "test    space gap" and not echo "test    space gap
                printf("%s ", token);
                // strcat(words, " "); strcat(words, token); // for history
                argc++;
            }
            printf("\n");
        }
        else if(cmp(token, "pwd")){
            pwd();
        }
        else if(cmp(token, "peek")){
            // assumption, flag is always given
            str argv[MAX_FILE_SIZE];
            int argc = 0;
            while((token = strtok(NULL, del)) != NULL){
                argv[argc] = calloc(MAX_FILE_SIZE, sizeof(char));
                strcpy(argv[argc++], token);
            }
            if(argc == 0){ 
                // assumptoin : if ls is called, ls -a is executed  (todo?)
                argv[argc] = calloc(MAX_FILE_SIZE, sizeof(char));
                strcpy(argv[argc++], "-a");
            }
            ls(argc, argv);

        }
        else if(cmp(token, "warp")){
            // assumption: previous paths become the stream of tokens and not the path from which stream of token is passed
            
            token = strtok(NULL, del);
            // if(token == NULL)
            
            cd(token, 1);
            while((token = strtok(NULL, del)) != NULL){
                cd(token, 1);
            }
            if(get_path(0, 0)[0] != '~' ) pwd();
        }
        else if(cmp(token, "pastevents")){
            // print_pe();
        }
        else if(cmp(token, "seek")){
            str argv[MAX_FILE_SIZE];
            int argc = 0;
            while((token = strtok(NULL, del)) != NULL){
                argv[argc] = calloc(MAX_FILE_SIZE, sizeof(char));
                strcpy(argv[argc++], token);
            }
            seek(argc, argv);
        }
        else if(cmp(token, "proclore")){
            int argc = 0, stew;
            while((token = strtok(NULL, del)) != NULL){
                argc++;
                stew = atoi(token);
            }
            if(argc == 0) proclore(getpid());
            else if (argc == 1) proclore(stew);
            else{
                perror("Invalid argumenets for proclore.");
            }
            
        }
        else{
            str argv[MAX_INPUT_LENGTH]; int argc = 0;
            argv[argc] = calloc(MAX_WORDS, sizeof(char));
            strcpy(argv[argc++], token);
            while((token = strtok(NULL, del)) != NULL){
                argv[argc] = calloc(MAX_FILE_SIZE, sizeof(char));
                strcpy(argv[argc++], token);
            }
            int status = 0;
            pid_t pid = fork();
            if(pid == 0){
                    if(execvp(*argv, argv) < 0){
                    printf("%s: command not found\n", *argv);
                   
                    fflush(stdout);
                    exit(EXIT_FAILURE); 
                }
            }
                
            else{
                waitpid(pid, &status, WUNTRACED);
                // if (waitpid(pid, &status, WNOHANG)== -1)
                //     perror("wait() error");
            }
        }
        
    }
}