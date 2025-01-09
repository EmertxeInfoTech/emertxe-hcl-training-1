
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int count = 100;
    while(count--) {
        printf("Thread running...\n");
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    printf("Waiting for thread to finish...\n");
    pthread_join(thread, NULL);
    printf("Thread finished.\n");
    return 0;
}
