#include "../include/main.h"
// %hhu for D_TYPE
// https://man7.org/linux/man-pages/man3/getgrouplist.3.html
// To print off_t:

// printf("%jd\n", (intmax_t)x);
// To print size_t:

// printf("%zu\n", x);
// To print ssize_t:

// printf("%zd\n", x);

void display_total(){
    struct stat filest;
    char *path = ".";
    stat(path, &filest);
    // TODO: always shows 8?

    printf("total %d\n", (int) filest.st_blocks);

}


void ls_a(int argc, str argv[]){

    struct dirent **namelist;
    int i,n;
    str dir;
    str currp = get_path(1, 0);
    str files = calloc(128, sizeof(char));
    if(cmp(argv[argc-1], "-a")) dir = ".";
    
    else dir = argv[argc - 1];
    if(cmp(dir, "~")) dir = get_home();

    if (chdir(dir) != 0) {
        perror("directory error");
        return; // Return an error code
    }
    
    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        for (i = 0; i < n; i++) {
            struct stat st = {0};
            stat(namelist[i]->d_name, &st);
            mode_t mode = st.st_mode;
            if(is_dir(mode)){
                blue(namelist[i]-> d_name);
            }else if(is_exe(mode)){
                green(namelist[i]-> d_name);
            }
            else 
                printf("%s\n", namelist[i]->d_name);
            free(namelist[i]);
            }
        }
    chdir(currp);
    free(namelist);
}


void ls_l(int argc, str argv[]){

    struct dirent **namelist;
    int i,n;
    str dir;
    str currp = get_path(1, 0);
    if(cmp(argv[argc-1], "-l")) dir = ".";
    else dir = argv[argc - 1];
    if(cmp(dir, "~")) dir = get_home();
    
    if (chdir(dir) != 0) {
        perror("directory error");
        return; // Return an error code
    }
    n = scandir(".", &namelist, NULL, alphasort);
    display_total();

    if (n < 0)
        perror("scandir");
    else {
        for (i = 0; i < n; i++) {
            struct stat st = {0};
            char date[32];
            stat(namelist[i]->d_name, &st);
            if(namelist[i]->d_name[0] == '.'){ // hidden file
                free(namelist[i]);
                continue;
            } 
            mode_t mode = st.st_mode;
            get_permissions(mode);
            struct passwd *pw = getpwuid(st.st_uid);  // error check for pw, gr = 0
            struct group *gr = getgrgid(st.st_gid); 
            printf("%d %s %s %jd ", (int) st.st_nlink, pw->pw_name, gr->gr_name, (intmax_t) st.st_size);
            strftime(date, 32, "%b %2d %2H:%2M", localtime(&(st.st_mtime)));
            printf("%s ", date);
            if(is_dir(mode)){
                blue(namelist[i]-> d_name);
            }else if(is_exe(mode)){
                green(namelist[i]-> d_name);
            }
            else 
                printf("%s\n", namelist[i]->d_name);
            free(namelist[i]);
            }
        }
    free(namelist);
    chdir(currp);
}

void ls_al(int argc, str argv[]){
    struct dirent **namelist;
    int i,n;
    str dir;
    str currp = get_path(1, 0);
    if(cmp(argv[argc-1], "-al")) dir = ".";
    else dir = argv[argc - 1];
    if(cmp(dir, "~")) dir = get_home();
    
    if (chdir(dir) != 0) {
        perror("directory error");
        return; // Return an error code
    }
    n = scandir(".", &namelist, NULL, alphasort);
    display_total();

    if (n < 0)
        perror("scandir");
    else {
        for (i = 0; i < n; i++) {
            struct stat st = {0};
            char date[32];
            stat(namelist[i]->d_name, &st);
            mode_t mode = st.st_mode;
            get_permissions(mode);
            struct passwd *pw = getpwuid(st.st_uid);  // error check for pw, gr = 0
            struct group *gr = getgrgid(st.st_gid); 
            printf("%d %s %s %jd ", (int) st.st_nlink, pw->pw_name, gr->gr_name, (intmax_t) st.st_size);
            strftime(date, 32, "%b %2d %2H:%2M", localtime(&(st.st_mtime)));
            printf("%s ", date);
            if(is_dir(mode)){
                blue(namelist[i]-> d_name);
            }else if(is_exe(mode)){
                green(namelist[i]-> d_name);
            }
            else 
                printf("%s\n", namelist[i]->d_name);
            free(namelist[i]);
            }
        }
    free(namelist);
    chdir(currp);
}



void ls(int argc, str argv[]){
    bool both = false;
    if(cmp(argv[0], "-al") || cmp(argv[0], "-la")) both = 1;
    bool only_a = false, only_l = false;
    if(!both){
        if(cmp(argv[0], "-l")){
            only_l = true;
            if(argc  == 1);
            else if (cmp(argv[1], "-a")){
                only_a = true; both = true;
            }
        }else if(cmp(argv[0], "-a")){
            only_a = true;
            if(argc == 1) ;
            else if (cmp(argv[1], "-l")){
                only_l = true; both = true;
            }
        }
    }
    if(both){
        ls_al(argc, argv);
    }
    else if(only_a){
        ls_a(argc, argv);
    }
    else if(only_l){
        ls_l(argc, argv);
    }else{
        perror("invalid flag");
    }
}