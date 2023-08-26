/*
TODO
root path, current path, 
*/
#include "../include/main.h"
// Constants
str ROOT_DIR;
str CURR_DIR;
str PREV_DIR;
str PREV_DIR_LS;
str CURR_DIR_LS;

void go_home(){
    CURR_DIR = ROOT_DIR; // home is the directory we invoked the program from
}
str get_home(){
    return ROOT_DIR;
}
// this is the home directory, where the program is invoked from
void invoke_path(){
    CURR_DIR = calloc(MAX_PATH_SIZE, sizeof(char));
    if(!getcwd(CURR_DIR, MAX_PATH_SIZE)){
        exit(0);
    }
    ROOT_DIR = CURR_DIR;
}
str relative_dir(str cwd){
    str ret_dir = calloc(MAX_PATH_SIZE, sizeof(char));
    int i = strlen(ROOT_DIR);
    strcpy(ret_dir, "~");
    for(; i<strlen(cwd); i++){
        // str t = cwd[i];
        char ch = cwd[i];
        strncat(ret_dir, &ch, 1);
    }
    return ret_dir;
    
}
str get_path(bool absolute, bool is_cd){
    if(CURR_DIR) free(CURR_DIR );
    if(!ROOT_DIR) invoke_path(); 
    CURR_DIR = calloc(MAX_PATH_SIZE, sizeof(char));
    if(!getcwd(CURR_DIR, MAX_PATH_SIZE)){
        exit(0);
    }
    if(absolute) return CURR_DIR;
    // printf("\n%s , %s \n", ROOT_DIR, CURR_DIR);
    if(cmpn(ROOT_DIR, CURR_DIR, min(strlen(ROOT_DIR), strlen(CURR_DIR))) && (strlen(CURR_DIR) >= strlen(ROOT_DIR))){
        return relative_dir(CURR_DIR);
    }
    if(is_cd) pwd();
    return CURR_DIR;
}
str get_prev_path(){
    if(!PREV_DIR) {
        perror("OLDPWD not set");
    }
   else
    return PREV_DIR;

}
void set_prev_path(str dir){
    if(PREV_DIR) free(PREV_DIR);
    PREV_DIR = calloc(MAX_PATH_SIZE, sizeof(char));
    strcpy(PREV_DIR, dir);
}
void pwd(){
    yellow(get_path(1, 0));
}
void cd(str dir, bool affect){
    
    str curr_path = get_path(1, 0);
    if(cmp(dir, "~")) dir = ROOT_DIR;
    else if(cmp(dir, ".")) return;
    else if(cmp(dir, "-")) dir = get_prev_path();
    // printf("\n%s\n", PREV_DIR);
    if (chdir(dir) != 0) {
        perror("directory error");
        return; // Return an error code
    }
    if(affect) set_prev_path(curr_path);
}


