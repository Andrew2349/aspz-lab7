#include <stdio.h>
#include <stdlib.h>

void display_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return;
    }
    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        count++;

        if (count == 20) {
            printf("--Press Enter to continue--");
            while (getchar() != '\n');
            count = 0;
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        printf("\n=== %s ===\n", argv[i]);
        display_file(argv[i]);
    }

    return 0;
}

