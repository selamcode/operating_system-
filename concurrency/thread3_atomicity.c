#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int counter = 0;  // Declare an atomic counter

void* increment(void* arg) {
    for (int i = 0; i < 1000; i++) {
        atomic_fetch_add(&counter, 1);  // Atomically increment the counter by 1
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads that will increment the counter
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print the final value of counter
    printf("Final counter value: %d\n", counter);  // Should print 2000
    return 0;
}

/*
Explanation:
atomic_int counter = 0;:

This declares an atomic integer. Using atomic_int ensures that all operations on this variable will be atomic and thus thread-safe.

atomic_fetch_add(&counter, 1);:

This is the atomic operation that increments counter by 1. It ensures that the increment is performed in a single, indivisible operation. This prevents race conditions when multiple threads are updating counter.

pthread_create:

This function creates two threads (t1 and t2), each calling the increment function.

pthread_join:

This ensures that the main thread waits for both threads (t1 and t2) to complete before printing the final value of counter.

Expected Output:

Since each thread increments the counter 1000 times, the expected final value of counter will be 2000.
*/