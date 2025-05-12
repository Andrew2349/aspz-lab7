#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *d;
    struct dirent *dir;
    char choice;

    d = opendir(".");
    if (d == NULL) {
        perror("opendir");
        return 1;
    }
    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;
        printf("%s - Delete this file? (y/n): ", dir->d_name);
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            if (remove(dir->d_name) == 0)
                printf("Deleted %s\n", dir->d_name);
            else
                perror("Error deleting file");
        } else {
            printf("Skipped %s\n", dir->d_name);
        }
    }

    closedir(d);
    return 0;
}
