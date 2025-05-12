#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    printf("Random float between 0.0 and 1.0:\n");
    for (int i = 0; i < 5; i++) {
        double rand_val = (double)rand() / RAND_MAX;
        printf("%f\n", rand_val);
    }
    double n;
    printf("\nEnter a value for n: ");
    scanf("%lf", &n);
    printf("Random float between 0.0 and %.2f:\n", n);
    for (int i = 0; i < 5; i++) {
        double rand_val = (double)rand() / RAND_MAX * n;
        printf("%f\n", rand_val);
    }

    return 0;
}
