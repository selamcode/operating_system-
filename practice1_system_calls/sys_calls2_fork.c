#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Start (PID: %d)\n", getpid());
    
    int rc1 = fork();  // First fork
    if (rc1 == 0) {
        printf("Child 1 (PID: %d, Parent: %d)\n", getpid(), getppid());
    } else {
        int rc2 = fork();  // Second fork, happens in the parent process
        if (rc2 == 0) {
            printf("Child 2 (PID: %d, Parent: %d)\n", getpid(), getppid());
        } else {
            printf("Parent (PID: %d) created two children: %d, %d\n", getpid(), rc1, rc2);
        }
    }
    
    return 0;
}

// in this case the second child would only copy the follwing code, starting from the second fork(), since it's the child of the first child

/*

    if (rc2 == 0) {
            printf("Child 2 (PID: %d, Parent: %d)\n", getpid(), getppid());
        } else {
            printf("Parent (PID: %d) created two children: %d, %d\n", getpid(), rc1, rc2);
        }

*/
