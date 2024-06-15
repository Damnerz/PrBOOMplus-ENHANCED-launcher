#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_FILE_NAME_LENGTH 256
#define MAX_MOUNT_POINT_LENGTH 256

//Verify if the path is correct.
void list_files(char *path) {
    DIR *dir;
    struct dirent *ent;
    dir = opendir(path);
    if (dir == NULL) {
        printf("Error opening directory\n");
        return;
    }
    printf("Files in %s:\n", path);
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
}

//Verify is c:/ d:/ etc...
void list_mount_points() {
    FILE *fp;
    char line[256];
    fp = fopen("/proc/mounts", "r");
    if (fp == NULL) {
        printf("Error opening /proc/mounts\n");
        return;
    }
    printf("Mount points:\n");
    while (fgets(line, 256, fp) != NULL) {
        char mount_point[MAX_MOUNT_POINT_LENGTH];
        sscanf(line, "%*s %s %*s %*s %*s %*s %*s", mount_point);
        printf("%s\n", mount_point);
    }
    fclose(fp);
}

//Print the files.
void list_files_on_device(char *mount_point) {
    char path[MAX_FILE_NAME_LENGTH];
    sprintf(path, "%s/", mount_point);
    list_files(path);
}

//Graphics print.
int main() {
    list_mount_points();
    char mount_point[MAX_MOUNT_POINT_LENGTH];
    printf("Enter mount point to list files: ");
    fgets(mount_point, MAX_MOUNT_POINT_LENGTH, stdin);
    mount_point[strlen(mount_point) - 1] = '\0'; // remove newline character
    list_files_on_device(mount_point);
    return 0;
}