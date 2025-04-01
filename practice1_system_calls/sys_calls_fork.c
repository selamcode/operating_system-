#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid()); // when we run sys_calls, it's the parent, since runnig  a program calls a fork() system call. 

    // After this, we are inside the child proces, since we called another fork()

    int rc = fork(); // fork() returns the PID 
    // int rc = -1; //  if we do this (or fork retuns number less than 0) there are no processes to run.

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // parent goes down this path (main)
        printf("parent of %d (pid:%d)\n",
        rc, (int) getpid());
    }
    return 0;
}


        // now when we call fork(), we will have the exact copy of this code, one for parent and another for child




        //                                      hello (parent)
        //                                      /      \
        //                           parent rc > 0     child rc == 0


        /*
        
        now which one running is decided by the OS so this program could output in on of the 2 ways
        
        1.
        hello (pid:24869)
        parent of 24870 (pid:24869)
        child (pid:24870) 
        OR

        2.
        hello (pid:24869)
        child (pid:24870)
        parent of 24870 (pid:24869)
        
        */