
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    while(1) {
        printf("Hello from thread: %ld\n", pthread_self());
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    while(1) {
        printf("Hi from main thread\n");
    }
    return 0;
}
