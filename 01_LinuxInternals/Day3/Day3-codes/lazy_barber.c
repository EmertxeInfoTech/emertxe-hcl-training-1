#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CHAIRS 3  // Number of chairs in the waiting room

int waiting_customers = 0;  // Number of customers waiting

void *barber(void *arg) {
    while (1) {
        if (waiting_customers > 0) {
            // Barber cuts hair
            printf("Barber: Cutting hair. Customers waiting: %d\n", waiting_customers);
            waiting_customers--;
            sleep(2);  // Simulate haircut time
        } else {
            // Barber sleeps if no customers
            printf("Barber: No customers. Sleeping...\n");
            sleep(1);
        }
    }
}

void *customer(void *arg) {
    int customer_id = *(int *)arg;

    if (waiting_customers < NUM_CHAIRS) {
        // Customer takes a seat
        waiting_customers++;
        printf("Customer %d: Waiting. Customers waiting: %d\n", customer_id, waiting_customers);
    } else {
        // No chairs available, customer leaves
        printf("Customer %d: No chair available. Leaving...\n", customer_id);
    }
    return NULL;
}

int main() {
    pthread_t barber_thread;
    pthread_create(&barber_thread, NULL, barber, NULL);

    // Simulate customers arriving at random intervals
    pthread_t customer_threads[10];
    for (int i = 0; i < 10; i++) {
        int *customer_id = malloc(sizeof(int));
        *customer_id = i + 1;
        sleep(rand() % 3);  // Random arrival time
        pthread_create(&customer_threads[i], NULL, customer, customer_id);
    }

    // Wait for all customer threads to complete
    for (int i = 0; i < 10; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    return 0;
}
