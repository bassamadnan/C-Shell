#ifndef MAIN_H
#define MAIN_H


// Libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>  
#include <sys/utsname.h>
#include <string.h>
#include <dirent.h>
#include <grp.h> // for group
#include <stdint.h>
#include <time.h>
#include <sys/wait.h> // wuncrate
#include <ctype.h>
#include <errno.h>
#include <time.h>
// #include <signal.h>

//  Definations
#define _GNU_SOURCE
#define str char*
#define str_arr char**
#define BUFFER_SIZE 4096
#define MAX_PATH_SIZE 4096
#define MAX_INPUT_LENGTH 4096
#define MAX_HOST_SIZE 512
#define MAX_FILE_SIZE 128
#define MAX_NAME_SIZE 1024
#define MAX_JOBS 64
#define MAX_WORDS 1024
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
// Structs
struct bgjob {
    int pid;        
    char command[64]; 
    bool isover;
    bool printed;
    bool normal;
    time_t start;
    time_t end;
};
extern struct bgjob bgarr[MAX_JOBS];
extern int bgc;




// Functions
str_arr input();
void echo();
void ls(int argc, str* argv);
void pwd();
void cd(str dir, bool affect);
str getUsername();
str replace(str input, char prev, str curr);
bool cmp(str s1, str s2);
void printPrompt();
void process(str cmd);
void invoke_path();
str get_path(bool full, bool is_cd);
bool cmpn(str s1, str s2, int n);
str get_prev_path();
str get_home();
void set_prev_path(str dir);
void green(str s);
void blue(str s);
void yellow(str s);
bool is_dir(mode_t mode);
bool is_exe(mode_t mode);
void get_permissions(mode_t mode);
void go_bg(str cmd);
int is_bg(str cmd);
void proclore(pid_t pid);
void remove_first_line();
void purge();
str get_pastevent(int n);
int check_pastevents(str x);
void write_pastevents(str_arr cmds);
void print_pe();
int substring_count(str string, str substring);
void seek(int argc, str argv[]);
bool is_reg(mode_t mode); 
void readAndPrintFile(const str filePath);
void print_bg();
#endif