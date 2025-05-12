#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;

    fp = popen("rwho | more", "r");

    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    pclose(fp);

    return 0;
}
