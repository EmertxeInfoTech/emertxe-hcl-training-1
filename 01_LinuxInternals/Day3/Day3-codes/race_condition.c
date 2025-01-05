
#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment_function(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_function, NULL);
    pthread_create(&thread2, NULL, increment_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", counter);
    return 0;
}
