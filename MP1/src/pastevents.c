#include "../include/main.h"

int file_lines() {
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return a negative value to indicate an error
    }

    int numLines = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            numLines++;
        }
    }

    fclose(file);
    return numLines;
}

void purge(){
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    ftruncate(fileno(fp), 0);
    fclose(fp);
}
void print_pe(){
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int line_count = 0;
    char line[MAX_INPUT_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;
        printf("%s",line);
    }
    fclose(file);
}



void printNthLine(int n) {
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int line_count = 0;
    char line[MAX_INPUT_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;
        if (line_count == n) {
            printf("Line %d: %s", n, line);
            fclose(file);
            return;
        }
    }

    if (n > line_count || n <= 0) {
        printf("Line %d does not exist in the file.\n", n);
    }

    fclose(file);
}

void remove_first_line(){
    
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Move the file pointer to the start of the second line
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            break;
        }
    }

    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    // Copy the remaining lines to the temporary file
    while ((c = fgetc(file)) != EOF) {
        fputc(c, tempFile);
    }

    // Close the original file
    fclose(file);

    // Reopen the original file in write mode
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error reopening file");
        fclose(tempFile);
        return;
    }

    // Copy the contents from the temporary file back to the original file
    rewind(tempFile);

    while ((c = fgetc(tempFile)) != EOF) {
        fputc(c, file);
    }

    // Close the files (tempFile will be cleaned up automatically)
    fclose(file);
}
int check_pastevents(str cmd){

    const char *patterns[] = {
        "pastevents execute 1",
        "pastevents execute 2",
        "pastevents execute 3",
        "pastevents execute 4",
        "pastevents execute 5",
        "pastevents execute 6",
        "pastevents execute 7",
        "pastevents execute 8",
        "pastevents execute 9",
        "pastevents execute 10",
        "pastevents execute 11",
        "pastevents execute 12",
        "pastevents execute 13",
        "pastevents execute 14",
        "pastevents execute 15"
    };
    
    int numPatterns = sizeof(patterns) / sizeof(patterns[0]);

    for (int i = 0; i < numPatterns; i++) {
        if (strcmp(cmd, patterns[i]) == 0) {
            return i + 1; // Return the pattern number (1-indexed)
        }
    }
    
    return -1; // No match found
}
str get_pastevent(int n){
    int x = n;
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Count the number of lines in the file
    int numLines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            numLines++;
        }
    }
    // Move the file pointer to the beginning of the line
    rewind(file);
    for (int i = 0; i < numLines - x; i++) {
        while ((ch = fgetc(file)) != EOF && ch != '\n');
    }
    
    // Read the desired line
    size_t bufferSize = MAX_INPUT_LENGTH; // Adjust buffer size as needed
    char *line = (char *)malloc(bufferSize);
    if (line == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }
    
    if (fgets(line, bufferSize, file) == NULL) {
        free(line);
        fclose(file);
        return NULL;
    }
    
    fclose(file);
    return line;
}

void write_pastevents(str_arr cmds){


    char cmd[MAX_INPUT_LENGTH] = "";
    for (int i = 0; cmds[i] != NULL; i++) {
        strcat(cmd, cmds[i]);
        if (cmds[i][strlen(cmds[i]) - 1] != '&') {
            strcat(cmd, ";");
        }
    }
    // printf("%d", strlen(cmd));
    cmd[(strlen(cmd))- 1] = '\0';
    // printf("WRITTEN COMMAND : %s \n", cmd);
    // Append the concatenated string to pastevents.txt
    str filename = calloc(MAX_PATH_SIZE, sizeof(char));
    strcat(filename, get_home());
    strcat(filename, "/src/pastevents.txt");
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    if(file_lines() >= 15) remove_first_line();
    
    if(cmd[strlen(cmd) - 2] == ';') cmd[(strlen(cmd))- 2] = '\0';
    
    fprintf(file, "%s", cmd);
    fclose(file);
}