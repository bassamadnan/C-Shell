#include "../include/main.h"

// https://stackoverflow.com/questions/29105448/get-process-info-from-proc?rq=3

void print_status(pid_t tgid) {
    // assumption status is printed as is

    char path[MAX_PATH_SIZE], line[100], *p;
    FILE *statusf;

    snprintf(path, sizeof(path), "/proc/%d/status", tgid);

    statusf = fopen(path, "r");
    if (!statusf) {
        perror("Failed to open status file");
        return;
    }

    while (fgets(line, sizeof(line), statusf)) {
        if (strncmp(line, "State:", 6) != 0) {
            continue;
        }

        // Ignore "State:" and whitespace
        p = line + 7;
        while (isspace(*p)) {
            ++p;
        }

        // Extract only the first character of the status
        char status = *p;
        printf("process status: %c", status);
        pid_t fg = tcgetpgrp(STDOUT_FILENO);
        if((status == 'R' || status == 'S') && (fg == __getpgid(tgid))) printf("+\n");
        else printf("\n");

        break;
    }

    fclose(statusf);
}

void process_group(pid_t pid){
    char path[MAX_PATH_SIZE], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%d/stat", pid);

    statusf = fopen(path, "r");
    if(!statusf)
        return;

    int pgrp, pid_read; char comm[256], state;
    if (fscanf(statusf, "%d %s %c %d", &pid_read, comm, &state, &pgrp) != 4) {
        perror("Error reading file");
        fclose(statusf);
        return;
    }
    fclose(statusf);
    printf("Process Group: %d\n", pgrp);
}

void virtual_memory(pid_t tgid) {
    char path[MAX_PATH_SIZE], line[100], *p;
    FILE* statusf;
    unsigned int vm;
    snprintf(path, 40, "/proc/%d/status", tgid);

    statusf = fopen(path, "r");
    if(!statusf)
        return;

    while(fgets(line, 100, statusf)) {
        if (sscanf(path, "VmSize: %u", &vm) == 1) {
            break;
        }
    }
    printf("Virtual memory: %u\n", vm);
    fclose(statusf);

}

void exe_path(pid_t pid){
    char exe_path[MAX_PATH_SIZE];
    size_t len;

    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);

    len = readlink(exe_path, exe_path, sizeof(exe_path) - 1);
    if (len == -1) {
        perror("Error reading symbolic link");
        // return 1;
    }
    exe_path[len] = '\0';

    printf("executable Path: %s\n", exe_path);
}
void proclore(pid_t pid){
    printf("pid : %d \n", (int) pid);
    print_status(pid);
    process_group(pid);
    virtual_memory(pid);
    exe_path(pid);

}