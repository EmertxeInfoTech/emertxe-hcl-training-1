#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define ARRAY_SIZE 10

// Structure to store person information
typedef struct {
    char *name;
    int age;
} Person;

// Function to initialize a person
Person* init_entity(const char *data, int value) {
    Person *entity = (Person *)malloc(sizeof(Person));
    if (!entity) {
        printf("Memory allocation failed for entity\n");
        return NULL;
    }

    // Allocating memory for name
    entity->name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    if (!entity->name) {
        printf("Memory allocation failed for data\n");
        free(entity);
        return NULL;
    }

    strcpy(entity->name, data); // Potential overflow if data > MAX_NAME_LENGTH
    entity->age = value;
    return entity;
}

// Function to release a person
void release_entity(Person *entity) {
    if (entity) {
        // Intentionally skipping freeing name to create a memory leak
        free(entity);
    }
}

// Function to display person details
void display_entity(Person *entity) {
    if (!entity || !entity->name) {
        printf("Invalid entity or entity data\n");
        return;
    }
    printf("Name: %s, Age: %d\n", entity->name, entity->age);
}

// Function to generate an array of integers
int* generate_dataset(int length) {
    int *dataset = (int *)malloc(length * sizeof(int));
    if (!dataset) {
        printf("Memory allocation failed for dataset\n");
        return NULL;
    }

    // Initialize dataset
    for (int i = 0; i < length; i++) {
        dataset[i] = i * 2;
    }
    return dataset;
}

// Function to discard an array
void discard_dataset(int *dataset) {
    free(dataset);
}

// Function to simulate improper memory usage
void improper_usage_demo() {
    int *temp = (int *)malloc(5 * sizeof(int));
    if (!temp) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        temp[i] = i + 1;
    }

    free(temp);

    // Accessing freed memory
    printf("Improper usage value: %d\n", temp[2]);
}

// Function to simulate boundary issues
void boundary_issue_demo() {
    int *buffer = generate_dataset(ARRAY_SIZE);

    // Accessing out-of-bounds memory
    printf("Boundary issue access: %d\n", buffer[ARRAY_SIZE + 1]);

    discard_dataset(buffer);
}

// Main function
int main() {
    // Initialize and display entity details
    Person *entity1 = init_entity("Alice", 30);
    display_entity(entity1);

    // Release entity (with memory leak for the name)
    release_entity(entity1);

    // Generate a dataset and forget to discard it (memory leak)
    int *dataset1 = generate_dataset(ARRAY_SIZE);

    // Initialize another entity and release it properly
    Person *entity2 = init_entity("Bob", 25);
    display_entity(entity2);
    release_entity(entity2);

    // Improper memory usage demonstration
    improper_usage_demo();

    // Boundary issue demonstration
    boundary_issue_demo();

    // Forget to discard the dataset
    // discard_dataset(dataset1);

    // Uncomment this line to discard the dataset
    // discard_dataset(dataset1);

    printf("Program completed. Check with Valgrind for memory issues.\n");
    return 0;
}
