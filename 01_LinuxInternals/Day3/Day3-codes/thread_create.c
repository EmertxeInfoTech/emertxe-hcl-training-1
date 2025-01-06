
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    while(1) {
        printf("Hello from thread!\n");\
    }
    return NULL;
}

int main() {
    pthread_t thread;
    printf("Hello from main thread!\n");
    pthread_create(&thread, NULL, thread_function, NULL);

    while (1) {
        printf("Hi from main thread\n");
    }
    return 0;
}
