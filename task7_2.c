#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_permissions(mode_t mode) {
    char permissions[11] = "----------";

    if (S_ISDIR(mode)) permissions[0] = 'd';
    else if (S_ISLNK(mode)) permissions[0] = 'l';

    if (mode & S_IRUSR) permissions[1] = 'r';
    if (mode & S_IWUSR) permissions[2] = 'w';
    if (mode & S_IXUSR) permissions[3] = 'x';
    if (mode & S_IRGRP) permissions[4] = 'r';
    if (mode & S_IWGRP) permissions[5] = 'w';
    if (mode & S_IXGRP) permissions[6] = 'x';
    if (mode & S_IROTH) permissions[7] = 'r';
    if (mode & S_IWOTH) permissions[8] = 'w';
    if (mode & S_IXOTH) permissions[9] = 'x';
    printf("%s ", permissions);
}

void print_file_info(const char *filename) {
    struct stat file_info;

    if (stat(filename, &file_info) == -1) {
        perror("stat");
        return;
    }
    print_permissions(file_info.st_mode);
    printf("%lu ", file_info.st_nlink);

    struct passwd *pwd = getpwuid(file_info.st_uid);
    if (pwd != NULL) {
        printf("%s ", pwd->pw_name);
    } else {
        printf("%d ", file_info.st_uid);
    }

    struct group *grp = getgrgid(file_info.st_gid);
    if (grp != NULL) {
        printf("%s ", grp->gr_name);
    } else {
        printf("%d ", file_info.st_gid);
    }
    printf("%lld ", (long long)file_info.st_size);

    char time_buf[20];
    struct tm *time_info = localtime(&file_info.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", time_info);
    printf("%s ", time_buf);
    printf("%s\n", filename);
}

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        print_file_info(entry->d_name);
    }
    closedir(dir);

    return 0;
}
