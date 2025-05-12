#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char *filename;
    char response[10];
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    printf("List of C source files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL) {
            stat(entry->d_name, &file_stat);
            if ((file_stat.st_mode & S_IROTH) == 0) {
                printf("%s - Do you want to allow read permission for others? (y/n): ", entry->d_name);
                fgets(response, sizeof(response), stdin);
                if (response[0] == 'y' || response[0] == 'Y') {
                    if (chmod(entry->d_name, file_stat.st_mode | S_IROTH) == 0) {
                        printf("Read permission granted for %s\n", entry->d_name);
                    } else {
                        perror("Failed to change permissions");
                    }
                } else {
                    printf("No changes made for %s\n", entry->d_name);
                }
            }
        }
    }
    closedir(dir);
    return 0;
}
