#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char *subdirs[100];
    int count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            if (is_directory(entry->d_name)) {
                subdirs[count] = strdup(entry->d_name);
                count++;
            }
        }
    }
    closedir(dir);
    qsort(subdirs, count, sizeof(char *), compare);
    printf("Subdirectories in alphabetical order:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", subdirs[i]);
        free(subdirs[i]);
    }

    return 0;
}

