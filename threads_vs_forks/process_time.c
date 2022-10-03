#include <stdio.h>
#include <time.h>

#define SLEEP 250000 // 1 second = 1000000 microseconds

void checkProcessingTime();

int main() {
    checkProcessingTime();
}

void checkProcessingTime() {
    clock_t begin = clock();
    for (int i = 0; i < 1000000000; i++); // Process to check processing time.
    clock_t end = clock();
    // CLOCKS_PER_SEC = 1000000
    double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC; // Pass result to seconds.
    printf("\nProcess took: %f seconds\n\n", timeSpent);
}
