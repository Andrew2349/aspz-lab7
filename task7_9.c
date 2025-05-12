#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start, end;
    start = clock();
    for (long i = 0; i < 100000000; i++) {
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Time taken for execution: %.2f ms\n", time_taken);

    return 0;
}

