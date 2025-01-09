
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
    printf("Thread received char: %c\n", data->ch);

    return NULL;
}

int main() {
    pthread_t thread;
    tdata_t var = {123, 'A'};
    pthread_create(&thread, NULL, thread_function, &var);
    pthread_join(thread, NULL);

    return 0;
}
