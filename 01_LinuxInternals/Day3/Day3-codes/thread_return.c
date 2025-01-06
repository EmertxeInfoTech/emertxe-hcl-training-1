#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Thread function to calculate factorial
void *factorial_function(void *arg) {
    int number = *(int *)arg;
    int *result = malloc(sizeof(int));
    *result = 1;

    for (int i = 1; i <= number; i++) {
        *result *= i;
    }

    printf("Thread: Factorial of %d is %d\n", number, *result);
    return result;  // Return the result
}

int main() {
    pthread_t thread;
    int number = 5;
    int *factorial_result;

    // Create thread to calculate factorial
    pthread_create(&thread, NULL, factorial_function, &number);

    // Wait for the thread to complete and retrieve the return value
    pthread_join(thread, (void **)&factorial_result);

    printf("Main Thread: Factorial of %d is %d\n", number, *factorial_result);

    // Free allocated memory
    free(factorial_result);

    return 0;
}
