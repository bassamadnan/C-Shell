#include "../include/main.h"
// helper for commands
void get_permissions(mode_t mode)
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
// https://www.javatpoint.com/find-occurrence-of-substring-in-c-using-function
int substring_count ( str string , str substring ) {  
  int i , j , l1 , l2;  
  int count = 0;  
  l1 = strlen ( string );  
  l2 = strlen ( substring );  
  
  for ( i = 0 ; i < l1 - l2 + 1 ; i++) {  
    if ( strstr ( string + i , substring ) == string + i ) {  
      count++;  
      i = i + l2 - 1 ;  
    }  
  }  
  return count ;  
} 
void readAndPrintFile(const str filePath){
    FILE *file = fopen(filePath, "r");

    if (file == NULL) {
        if (errno == EACCES) {
            fprintf(stderr, "Permission denied to open '%s'\n", filePath);
        } else {
            perror("Error opening file");
        }
        return;
    }

    char buffer[MAX_INPUT_LENGTH];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

void print_bg(){
    for(int i=0; i<bgc; i++){
        if(bgarr[i].isover && !bgarr[i].printed){
            if(bgarr[i].normal){
                printf("%s with pid: %d exited normally\n", bgarr[i].command, bgarr[i].pid);
            }else{
                printf("%s with pid: %d exited abnormally\n", bgarr[i].command, bgarr[i].pid);

            }
            bgarr[i].printed = 1;
        }
    }
    
}