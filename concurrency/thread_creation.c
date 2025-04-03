// 1
#include <stdio.h>
#include <pthread.h>

void *mythread(void *arg) {
    printf("%s\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {

    // creating a thread variable
    pthread_t thread1, thread2;
    
    printf("main: begin\n");

    // creating threads
    pthread_create(&thread1, NULL, mythread, "A");
    pthread_create(&thread2, NULL, mythread, "B");
    
    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("main: end\n");
    return 0;
}

/*
The output could be different depnding on the how the scheduler decides to run them.

Trace 1 (Threads execute in order)

main: begin
A
B
main: end


Trace 2 (Threads execute out of order)

main: begin
B
A
main: end


Trace 3 (Interleaved execution)

main: begin
A
main: end
B

*/


/*

pthread_t is a data type used in POSIX threads (pthreads) to represent a thread.
When you create a thread using pthread_create(), it assigns a unique identifier
to that thread using a pthread_t variable.

*/

/*

The main() function makes sure that:

    All threads finish their work before main() exits.

    It doesn’t exit too early, leaving unfinished threads running.

How Does It Do That?
By using pthread_join(), main() waits for the created threads to complete before it exits.

 */

