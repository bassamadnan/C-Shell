
#include "include/main.h"
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
void blue(str s)
{
    printf("\033[1;34m%s\033[0m\n", s);
}
void display_permissions_ls(mode_t mode)
{
    char s[32]; int i = 0;
    //for the file type
    if (S_ISREG(mode))
        s[i]= '-';
    else if (S_ISDIR(mode))
        s[i] = 'd';
    else if (S_ISCHR(mode))
        s[i] = 'c';
    else if (S_ISBLK(mode))
        s[i] = 'b';
    else if (S_ISFIFO(mode))
        s[i] = 'f';
    else if (S_ISLNK(mode))
        s[i] = 'l';
    else
        s[i] = 's';

    i++;
    //for all the permissions
    s[i++] = (mode & S_IRUSR) ? 'r' : '-';
    s[i++] = (mode & S_IWUSR) ? 'w' : '-';
    s[i++] = (mode & S_IXUSR) ? 'x' : '-';
    s[i++] = (mode & S_IRGRP) ? 'r' : '-';
    s[i++] = (mode & S_IWGRP) ? 'w' : '-';
    s[i++] = (mode & S_IXGRP) ? 'x' : '-';
    s[i++] = (mode & S_IROTH) ? 'r' : '-';
    s[i++] = (mode & S_IWOTH) ? 'w' : '-';
    s[i++] = (mode & S_IXOTH) ? 'x' : '-';
    s[i++] = ' ';
    s[i++] = '\0';
    printf("%s", s);
    
}
// struct proccess{
//     pid_t id;
//     char name[MAX_NAME_SIZE];
// };
// struct proccess cur_fg;
// struct proccess job_list[MAX_JOBS];
// int jobc = 0;

int main(){
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "src/pastevents.txt");
    printf("%s", filename);
  return 0;
}