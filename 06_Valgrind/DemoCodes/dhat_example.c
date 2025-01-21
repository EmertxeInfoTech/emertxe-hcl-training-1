
#include <stdlib.h>

void allocate() {
    int *arr = malloc(100 * sizeof(int));
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    free(arr);
}

int main() {
    allocate();
    return 0;
}
