//Create, Edit, Open and delete text files with extensions too, it can be use for .cfg files or .conf files and be used devices with "C" language and a terminal.
//To delete a file you should Re-write the same name than the other file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FILE_NAME_LENGTH 256

//Create the file with the name and the extension (example: .png .wad .pk3)
void create_file(char *file_name) {
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;
    }
    //command "exit" to save and quit the file.
    printf("Enter text (type 'exit' to save and exit):\n");
    char line[MAX_LINE_LENGTH];
    while (1) {
        fgets(line, MAX_LINE_LENGTH, stdin);
        if (strcmp(line, "exit\n") == 0) {
            break;
        }
        fprintf(fp, "%s", line);
    }
    fclose(fp);
}

//Open the file but you need to know how to write the name of the file.
void open_file(char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp)!= NULL) {
        printf("%s", line);
    }
    fclose(fp);
}

//Edit the file same as open_file.
void edit_file(char *file_name) {
    FILE *fp = fopen(file_name, "a");
    if (fp == NULL) {
        printf("Error editing file\n");
        return;
    }
    printf("Enter text (type '/exit' to save and exit):\n");
    char line[MAX_LINE_LENGTH];
    while (1) {
        fgets(line, MAX_LINE_LENGTH, stdin);
        if (strcmp(line, "/exit\n") == 0) {
            break;
        }
        fprintf(fp, "%s", line);
    }
    fclose(fp);
}

//Name of the file and graphics
int main() {
    char file_name[MAX_FILE_NAME_LENGTH];
    printf("Enter file name: ");
    fgets(file_name, MAX_FILE_NAME_LENGTH, stdin);
    file_name[strlen(file_name) - 1] = '\0'; // remove newline character
    int choice;
    printf("1. Create file\n2. Open file\n3. Edit file\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            create_file(file_name);
            break;
        case 2:
            open_file(file_name);
            break;
        case 3:
            edit_file(file_name);
            break;
        default:
            printf("Invalid choice\n");
    }
    return 0;
}