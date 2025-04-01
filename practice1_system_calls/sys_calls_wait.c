#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello (pid:%d)\n", (int)getpid());

    // Create a new process using fork
    int rc = fork();

    if (rc < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }

    // Child process (rc == 0)
    if (rc == 0) {
        printf("Child (pid:%d)\n", (int)getpid());
    } 
    // Parent process (rc > 0)
    else {
        // Wait for the child process to complete
        int rc_wait = wait(NULL);
        printf("Parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
    }

    return 0;
}

/*
With the wait() system call, the parent process will wait for the child process to finish before it continues executing. So the order of execution will now be more predictable.

Here's how it works step-by-step:
The program starts, and the parent process (the original process) prints the message "Hello (pid: [parent_pid])".

The fork() system call is made, and a child process is created. Now there are two processes:

The parent process continues from the fork() call and will enter the else block.

The child process executes the code inside the if (rc == 0) block.

In the child process:

The child prints "Child (pid: [child_pid])".

Then the child process finishes and terminates.

Meanwhile, the parent process executes:

The parent reaches the wait(NULL) call. This causes the parent to wait for the child process to finish before continuing.

After the child finishes, the parent proceeds to the next line and prints "Parent of [child_pid] (rc_wait: [rc_wait_value]) (pid: [parent_pid])".

*/
