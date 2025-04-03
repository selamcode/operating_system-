#include <stdio.h>
#include <pthread.h>

#define NUM_ITERATIONS 10000

static volatile int counter = 0;

void *mythread(void *arg) {
    printf("%s: begin\n", (char *)arg);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        counter++;
    }
    printf("%s: done\n", (char *)arg);
    return NULL;
}

int main() {
    pthread_t p1, p2;
    
    printf("main: begin (counter = %d)\n", counter);
    
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    printf("main: done with both (counter = %d)\n", counter);
    
    return 0;
}


/*

he issue lies in the fact that Thread 1 is interrupted right after it reads the value of counter (which is 0), but before it has a chance to write the updated value back. Meanwhile, Thread 2 also reads counter, which is still 0, and performs its update. When Thread 1 resumes, it doesn't know that Thread 2 has already updated the value, so it overwrites counter with its own result.

Let me break this down further with your example:

Step-by-Step Breakdown:
Thread 1 starts execution:

Thread 1 reads counter, which is 0, and stores it in a temporary variable (temp).


temp = counter; // temp = 0
Thread 1 is interrupted by the OS:

The OS saves the state of Thread 1 (its registers, including temp), and switches to Thread 2.

Thread 2 starts executing:

Thread 2 also reads counter, which is still 0, and stores it in its temporary variable (temp2).


temp2 = counter; // temp2 = 0
Thread 2 updates counter:

Thread 2 adds 1 to temp2 (so temp2 = 1) and writes it back to counter.


counter = temp2; // counter = 1
Thread 1 resumes execution:

Thread 1 resumes execution after the interrupt. Since it still has the old value of temp = 0, it updates counter to 1 (the same value Thread 2 wrote).


counter = temp; // counter = 1 (again)
Final Outcome:
The final value of counter is 1, instead of 2, because Thread 1 overwrote the change made by Thread 2 without seeing it.

Thread 1 never saw the update made by Thread 2 because it was interrupted and didn't recheck the value of counter before writing back.

Key Concept: Why the Overwrite Happens
When Thread 1 reads counter, it stores the value in a temporary variable (temp).

Thread 1 doesn't know that Thread 2 has changed counter in the meantime because it was interrupted before it could write back.

Thread 1 writes back its own value (temp), which was 0, overwriting Thread 2's update, which was 1.

This is a classic race condition caused by lack of synchronization. Both threads are trying to update the same shared resource (counter) without any mechanism to ensure that one thread's update doesn’t overwrite the other’s.

*/




/*

The issue is indeed related to the interruptions (or context switches) between threads, which leads to race conditions. Let me explain it step by step:

Global Variables and Memory
Global Variables:

counter is a global variable, meaning it exists in a shared memory space that both threads can access.

The variable itself is stored in a shared location in memory (usually in the data segment), and its value is accessible to all threads in the program.

Thread Stacks:

Each thread has its own stack where it stores its local variables and the execution context (such as registers and return addresses).

The global variable counter, however, is not part of the thread's stack. It's stored in a shared memory space that is accessible by all threads.

Both threads can access and modify counter at the same time since it is shared.

How CPU Interruptions (Context Switching) Cause the Issue
The real problem here is how the CPU schedules threads. The interrupts or context switches are managed by the operating system, and they allow different threads to run in an interleaved manner. This is where race conditions can occur.

Let me explain what happens in the thread execution sequence with context switching:

Thread Execution with Context Switching
Let's assume counter = 0 initially.

Thread 1 starts and reads the value of counter.

It reads counter = 0 and stores this in a local register (say, eax in assembly).

Thread 1 is interrupted by the OS (due to a timer or any reason), and the CPU context switches to Thread 2.

Thread 1’s state (its registers, including the value of eax) is saved in the thread's control block (TCB) by the OS.

Thread 2 starts executing, and it also reads counter = 0 (the same value that Thread 1 read).

Thread 2 increments counter and writes it back to the global memory location, so counter = 1.

Thread 1 resumes from where it left off, with eax = 0 (the value it stored before the interruption).

It increments its own register value to eax = 1, and writes it back to counter.

Now, the value of counter is overwritten by Thread 1’s update, even though Thread 2 had already updated it to 1.

Final counter value: 1 instead of 2.

Why This Happens (Race Condition)
The issue is the time gap between when Thread 1 reads counter and when it writes the updated value.

Thread 2 can also read the same value for counter during that gap, and both threads end up writing their result back to the same location in memory, causing a lost update.

The problem isn't that the variable counter isn't saved or available—it's in shared memory. The problem lies in the fact that the threads are updating the variable without any synchronization. This causes the race condition: both threads read the same value, modify it, and write it back, but the updates conflict.

CPU Interrupts and Context Switching:
The CPU interrupting Thread 1 before it writes to counter causes Thread 2 to execute its increment first.

When Thread 1 resumes, it writes to counter, overwriting the value that Thread 2 wrote.

This happens because each thread starts execution without knowing the other's state, leading to updates that are based on outdated values.

Summary:
Global variables are shared between threads, and both can access and modify them.

Thread stacks are separate, but the global variable counter is not part of the stack—it's in shared memory.

The issue arises because the CPU can interrupt a thread in the middle of its execution, leading to context switches where another thread starts executing.

Without synchronization (like a mutex), both threads can read the same value, modify it, and write it back, causing race conditions and lost updates.



*/
