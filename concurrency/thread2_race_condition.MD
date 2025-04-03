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

