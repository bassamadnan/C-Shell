#include "../include/main.h"

int tot_lines = 0;
str getUsername(){
    struct passwd *p;
    uid_t  uid;

    if ((p = getpwuid(uid = getuid())) == NULL)
        perror("getpwuid() error");

    else 
        return p->pw_name;
}

void printPrompt(){
    char *user_name = getUsername();
    char hostname[MAX_HOST_SIZE];
    gethostname(hostname, MAX_HOST_SIZE);
    char cwd[MAX_PATH_SIZE];
    // printf("<%s@%s>%s: ",getlogin(), hostname, get_path(0, 0));
    printf("<\033[1;32m%s@%s\033[0m>\033[1;34m%s\033[0m: ", getlogin(), hostname, get_path(0, 0)); 

}
str_arr break_line(str in){
    in = replace(in, '&', "&;");

    str_arr cmds = (str_arr) calloc(20, sizeof(str));
    char *token, *savptr = in;
    int i = 0;
    while((token = strtok_r(savptr, ";", &savptr))){
      cmds[i] = (char*)malloc(1024*sizeof(char));
      strcpy(cmds[i++], token);
    }
    write_pastevents(cmds);
    return cmds;
}
str_arr input(){
    
    // char in[BUFFER_SIZE];
    str in = calloc(BUFFER_SIZE, sizeof(char));
    char *temp = NULL;
    do{
      temp = fgets(in, BUFFER_SIZE, stdin);
      // printf("%s -> %d\n ", in, (int)strlen(in));
    }while(temp == NULL);
    in = replace(in, '&', "&;");

    str_arr cmds = (str_arr) calloc(20, sizeof(str));
    char *token, *savptr = in;
    int i = 0;
    while((token = strtok_r(savptr, ";", &savptr))){
      cmds[i] = (char*)malloc(1024*sizeof(char));
      strcpy(cmds[i++], token);
    }
    bool flag = true;
    //     for(int x=0; cmds[x] != NULL;  x++){
    //   printf("%s\n", cmds[x]);
    // }
    for(int x=0; cmds[x] != NULL; x++){
        if(cmp(cmds[x], "pastevents")){
            flag = false; // dont write command
            print_pe();
        }
        if(cmp(cmds[x], "pastevents purge")){
            tot_lines = 0;
            flag = false;
            purge(); // erase the txt file
        }
    }
    if(flag){
        // have to write the command in the txt file
        // replace pastevents execute x with the x'th line
        bool wrote = false;
        for(int x=0; cmds[x] != NULL; x++){

            int check = check_pastevents(cmds[x]);
            if(check == -1) continue; // not a pastevent execute line
            int lineno = tot_lines - check + 1;
            // printf("%d line no", check);
            // if(lineno < 0){
            //     perror("Invalid pastevent execute request");
            // }
            cmds[x] = get_pastevent(check);
            if(check != 1) { wrote = true; write_pastevents(cmds);}
            if(check == 1) wrote = true;
            if(substring_count(cmds[x], ";") >= 1)
                return break_line(cmds[x]);
        }
        if(!wrote) write_pastevents(cmds);
        tot_lines ++;
    }
    // for(int x=0; cmds[x] != NULL;  x++){
    //   printf("%s\n", cmds[x]);
    // }
    return cmds;
}

