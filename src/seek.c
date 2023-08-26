#include "../include/main.h"
int done = 0;
int reccall = 0;
char nxtpath[MAX_PATH_SIZE];
char stratpath[MAX_PATH_SIZE];

str getBaseName(str filename) {
    const char *lastDot = strrchr(filename, '.'); 

    if (lastDot == NULL) {
        return filename; 
    } else {
        size_t baseLength = (size_t)(lastDot - filename);
        str baseName = (char *)malloc(baseLength + 1);
        strncpy(baseName, filename, baseLength);
        baseName[baseLength] = '\0';
        
        return baseName;
    }
}
void explore_flage(str path,str targetName, bool flagd, bool flagf) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }
    
    struct dirent *entry;
    
    while ((entry = readdir(dir)) != NULL) {
        if (cmp(entry->d_name, ".")|| cmp(entry->d_name, "..")) {
            continue;
        }
        str temp = calloc(MAX_NAME_SIZE, sizeof(char));
        temp = getBaseName(entry->d_name);
        // printf("%s\n", temp);
        if(flagf && cmp(temp, targetName) && !(cmp(temp, entry->d_name))){
            char tp[MAX_PATH_SIZE];
            snprintf(tp, sizeof(tp), "%s/%s", path, entry->d_name);
            if(!done){
                green(tp);
                strcpy(nxtpath, get_path(1, 0));
                strcat(nxtpath, "/");
                strcat(nxtpath, tp);
                // if(access(nxtpath, R_OK | X_OK) != 0){
                //     done = 1;
                //     printf("%s \n", nxtpath); // perfect
                //     printf("Missing permissions for task!\n");
                // }
                // else{

                    readAndPrintFile(nxtpath);
                    printf("\n");
                    done = 1;
                // }
            }
        }
        char newEntryPath[MAX_PATH_SIZE];
        snprintf(newEntryPath, sizeof(newEntryPath), "%s/%s", path, entry->d_name);
        struct stat st = {0};
        stat(entry->d_name, &st);
        mode_t mode = st.st_mode;
        if (entry->d_type == DT_DIR) {
            if(flagd && cmp(entry->d_name, targetName)){
                if(!done){
                    strcpy(nxtpath, get_path(1, 0));
                    // printf("%s, \n", nxtpath);
                    strcat(nxtpath, "/");
                    strcat(nxtpath, newEntryPath);
                    done =  1;
                    blue(newEntryPath);

                    if (chdir(nxtpath) != 0) {
                    done = 0;
                    perror("directory error");
                    return; // Return an error code
                    }

                }
            } 
            // explore_flage(newEntryPath, targetName, flagd, flagf);
        }
    }
    
    closedir(dir);
}

void exploreDirectory(str path,str targetName, bool flagd, bool flagf) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }
    
    struct dirent *entry;
    
    while ((entry = readdir(dir)) != NULL) {
        if (cmp(entry->d_name, ".")|| cmp(entry->d_name, "..")) {
            continue;
        }
        str temp = calloc(MAX_NAME_SIZE, sizeof(char));
        temp = getBaseName(entry->d_name);
        // printf("%s\n", temp);
        if(flagf && cmp(temp, targetName) && !(cmp(temp, entry->d_name))){
            char tp[MAX_PATH_SIZE];
            snprintf(tp, sizeof(tp), "%s/%s", path, entry->d_name);
            reccall++;
            green(tp);
        }
        char newEntryPath[MAX_PATH_SIZE];
        snprintf(newEntryPath, sizeof(newEntryPath), "%s/%s", path, entry->d_name);
        struct stat st = {0};
        stat(entry->d_name, &st);
        mode_t mode = st.st_mode;
        if (entry->d_type == DT_DIR) {
            if(flagd && cmp(entry->d_name, targetName)) blue(newEntryPath);
            reccall++;
            exploreDirectory(newEntryPath, targetName, flagd, flagf);
        }
    }
    
    closedir(dir);

}

void seek(int argc, str argv[]){
    if(argc == 0){
            perror("invalid input");
    }
    str flags[] = {"-d", "-f", "-e"};
    bool flagd = false, flagf = false, flage = false;
    int lstflag = -1;
    for(int i=0; i<argc; i++){
        for(int j=0; j<3; j++){
            if(cmp(argv[i], flags[j])){
                if(j == 0) flagd = true;
                if(j == 1) flagf = true;
                if(j == 2) flage = true;
                lstflag = max(lstflag, i);
            }
        }
    }
    if(lstflag + 1 >= argc){
        perror("invalid input");
        return;
    }
    if(flagd && flagf){
        perror("invalid flags");
        return;
    }
    str search = argv[lstflag + 1];
    if(lstflag == -1){
        // no flags were given
        if(argc == 2){
            str dir = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(dir,argv[argc - 1]);
            str currp = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(currp, get_path(1, 0));
            if (chdir(dir) != 0) {
                 perror("directory error");
                return; // Return an error code
            }
            exploreDirectory(".", search, 1, 1);
            if(reccall ==0) printf("No files or directories found! \n");

            chdir(currp);
        }else if(argc == 1){
            exploreDirectory(".", search, 1, 1);
            if(reccall ==0) printf("No files or directories found! \n");

        }else{
            perror("Invalid input");
            return;
        }
    }
    // path given
    // path idx = lstflag + 2
    if(lstflag + 2 < argc){
        if(!flage){
            str dir = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(dir,argv[argc - 1]);
            str currp = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(currp, get_path(1, 0));
            chdir(dir);
            exploreDirectory(".", search, flagd, flagf);
            chdir(currp);
            if(reccall ==0) printf("No files or directories found! \n");


        }else if(flage){
            str dir = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(dir,argv[argc - 1]);
            str currp = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(currp, get_path(1, 0));
            if (chdir(dir) != 0) {
                 perror("directory error");
                return; // Return an error code
            }
            if(flagd){
                strcpy(stratpath, get_path(1, 0));
            }
            explore_flage(".", search, flagd, flagf);
            if(!flagd) chdir(currp);
            if(done) set_prev_path(stratpath);
            if(!done) printf("No files or directories found! \n");

        }
    }
    else{
        // search  in current directory
        if(!flage){
            exploreDirectory(".", search, flagd, flagf);
            if(reccall ==0) printf("No files or directories found! \n");

        }
        else if(flage){
            explore_flage(".", search, flagd, flagf);
            if(!done) printf("No files or directories found! \n");
        }
    }
    done = 0; reccall=0;
}