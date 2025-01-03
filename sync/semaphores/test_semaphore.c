#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// Initialize semaphores
sem_t mutex;
sem_t next;
int next_count = 0;

void* procedure(void* arg) {
    printf("Procedure: Waiting for mutex\n");
    sem_wait(&mutex);
    printf("Procedure: Entered critical section\n");
    // Body of procedure
    if (next_count > 0) {
        sem_post(&next);
    } else {
        sem_post(&mutex);
    }
    printf("Procedure: Exiting critical section\n");
    return NULL;
}

void* another_procedure(void* arg) {
    sem_t x_sem;
    int x_count = 0;

    sem_init(&x_sem, 0, 0);

    x_count = x_count + 1;
    printf("Another Procedure: Waiting for mutex\n");
    sem_wait(&mutex);
    printf("Another Procedure: Entered critical section\n");
    if (next_count > 0) {
        sem_post(&next);
    } else {
        sem_post(&mutex);
    }

    printf("Another Procedure: Waiting for x_sem\n");
    sem_wait(&x_sem);
    x_count = x_count - 1;
    if (x_count > 0) {
        next_count = next_count + 1;
        sem_post(&x_sem);
        sem_wait(&next);
        next_count = next_count - 1;
    }
    printf("Another Procedure: Exiting critical section\n");
    sem_destroy(&x_sem);
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&next, 0, 0);

    // Create threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, procedure, NULL);
    pthread_create(&thread2, NULL, another_procedure, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&next);

    return 0;
}
