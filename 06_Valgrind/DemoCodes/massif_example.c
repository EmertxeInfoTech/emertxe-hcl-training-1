
#include <stdlib.h>
#include <string.h>

void allocate_memory() {
    char *buffer = malloc(100 * 1024); // Allocate 100 KB
    memset(buffer, 0, 100 * 1024);
    free(buffer);
}

int main() {
    for (int i = 0; i < 10; i++) {
        allocate_memory();
    }
    return 0;
}
