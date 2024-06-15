#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void list_files(const char *path, int level) {
    DIR *dir;
    struct dirent *ent;
    char indent[1024];

    // Create indentation string
    for (int i = 0; i < level; i++) {
        strcat(indent, "---->");
    }

    // Open directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Iterate over directory entries
    while ((ent = readdir(dir))!= NULL) {
        char filepath[1024];
        struct stat statbuf;

        // Skip. and..
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        // Create full path
        snprintf(filepath, sizeof(filepath), "%s/%s", path, ent->d_name);

        // Get file status
        if (stat(filepath, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        // Print directory entry (all the files)
        if (S_ISDIR(statbuf.st_mode)) {
            printf("%s%s\n", indent, ent->d_name);
            list_files(filepath, level + 1);
        } else {
            printf("%s%s\n", indent, ent->d_name);
        }
    }

    // Close directory
    closedir(dir);
}

//Enter the path.
int main() {
    char path[1024];
    printf("Enter a path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = 0; // Remove newline character

    list_files(path, 0);

    return 0;
}