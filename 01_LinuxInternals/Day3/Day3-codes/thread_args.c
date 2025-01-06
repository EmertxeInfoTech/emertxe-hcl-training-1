
#include <stdio.h>
#include <pthread.h>
typedef struct thread_data
{
    int count;
    char ch;
}tdata_t;


void *thread_function(void *arg) {

    tdata_t *data = (tdata_t *)arg;

    printf("Thread received number: %d\n", data->count);
    printf("Thread received char: %ch\n", data->ch);

    return NULL;
}

int main() {
    pthread_t thread;
    int number = 42;

    pthread_create(&thread, NULL, thread_function, &number);
    pthread_join(thread, NULL);

    return 0;
}
