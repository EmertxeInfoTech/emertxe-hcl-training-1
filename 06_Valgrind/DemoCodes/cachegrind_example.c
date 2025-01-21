
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000

void access_memory() {
    int *array = (int *)malloc(SIZE * SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array[i * SIZE + j] = i + j; // Row-major order
        }
    }
    free(array);
}

int main() {
    access_memory();
    return 0;
}
