#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();  // Fork a new process
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process: redirect standard output to a file
        close(STDOUT_FILENO);  // Close the standard output (file descriptor 1)
        open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);  // Open the file for writing

        // Prepare arguments for the execvp call (to run "wc" program)
        char *myargs[3];
        myargs[0] = strdup("wc");   // Program name: wc
        myargs[1] = strdup("p4.c"); // Argument: file to count words in
        myargs[2] = NULL;           // Mark end of argument array

        execvp(myargs[0], myargs);  // Execute the wc program on "p4.c"
    } else {
        // Parent process
        int rc_wait = wait(NULL);  // Wait for the child process to finish
    }
    
    return 0;  // Return success
}


// execvp() is one of the variations of the exec() family

/*

if you open p4.output


Here's what each number means:

8: This is the number of lines in the p4.c file. It tells you how many lines of text are in the file.

17: This is the number of words in the p4.c file. It counts all the words, where a word is typically defined as any sequence of characters separated by whitespace.

142: This is the number of characters in the p4.c file, including all letters, digits, spaces, and punctuation marks.

p4.c: This is the name of the file that the wc command has analyzed.

Summary of what the numbers mean:
8: Number of lines in p4.c

17: Number of words in p4.c

142: Number of characters in p4.c

p4.c: The file being analyzed by the wc command

*/