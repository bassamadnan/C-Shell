#include "../include/main.h"
int done = 0;
char nxtpath[MAX_PATH_SIZE];

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
            green(tp);
            if(!done){
                readAndPrintFile(path);
                done = 1;
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
                    strcpy(nxtpath, path);
                    done =  1;
                }
                blue(newEntryPath);
            } 
            explore_flage(newEntryPath, targetName, flagd, flagf);
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
            green(tp);
        }
        char newEntryPath[MAX_PATH_SIZE];
        snprintf(newEntryPath, sizeof(newEntryPath), "%s/%s", path, entry->d_name);
        struct stat st = {0};
        stat(entry->d_name, &st);
        mode_t mode = st.st_mode;
        if (entry->d_type == DT_DIR) {
            if(flagd && cmp(entry->d_name, targetName)) blue(newEntryPath);
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

            chdir(currp);
        }else if(argc == 1){
            exploreDirectory(".", search, 1, 1);
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

        }else if(flage){
            str dir = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(dir,argv[argc - 1]);
            str currp = calloc(MAX_PATH_SIZE, sizeof(char));
            strcpy(currp, get_path(1, 0));
            if (chdir(dir) != 0) {
                 perror("directory error");
                return; // Return an error code
            }
            explore_flage(".", search, flagd, flagf);
            if(flagd){
                chdir(nxtpath);
            }
            chdir(currp);
        }
    }
    else{
        // search  in current directory
        if(!flage){
            exploreDirectory(".", search, flagd, flagf);
        }
        else if(flage){
            explore_flage(".", search, flagd, flagf);

        }
    }
}