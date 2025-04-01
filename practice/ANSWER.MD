1. Run process-run.pywith the following flags: -l 5:100,5:100.
What should the CPU utilization be (e.g., the percent of time the
CPU is in use?) Why do you know this? Use the -c and -p flags to
see if you were right.

```

it is 100 % because in the reame it is clear that we have process that are comma separated in the form of 

X1:Y1,X2:Y2 where X is the number of instructions that process should run, and Y the chances (from 0 to 100)

so 5 is number of instruction and 100 is the chance of that instruction use the CPU which is 100%.

 a comma-separated list of processes to run, in the
                        form X1:Y1,X2:Y2,... where X is the number of
                        instructions that process should run, and Y the
                        chances (from 0 to 100) that an instruction will use
                        the CPU or issue an IO

```
2. Now run with these flags: ./process-run.py -l 4:100,1:0.
These flags specify one process with 4 instructions (all to use the
CPU), and one that simply issues an I/O and waits for it to be done.
How long does it take to complete both processes? Use -c and -p
to find out if you were right.

```
Breakdown of Execution:
Process 0 (PID 0) runs first

It has 4 CPU instructions, so it runs for 4 time units (ticks).

At time 5, it completes.

Process 1 (PID 1) starts

It issues an I/O request at time 5 and becomes blocked.

The I/O takes 5 time units to complete (from time 6 to 10).

At time 11, the I/O completes, and the process finishes.

Total execution time: 11 time units

CPU & I/O Usage:
CPU is used for:

4 time units by PID 0 (CPU instructions).

1 time unit when PID 1 completes after I/O (time 11).

1 additional unit when issuing the I/O request (time 5).

Total: 6 time units of CPU usage.

I/O is used for:

5 time units (from time 6 to 10).

CPU Distribution:
PID 0 used 4 out of 6 CPU time units → 
4/6×100=66.7%
6/4×100=66.7%

PID 1 used 2 out of 6 CPU time units → 
2/6×100=33.3%


Final Answer:
Total execution time: 11 clock ticks

CPU usage breakdown:

PID 0: 66.7%

PID 1: 33.3%

```

3. Switch the order of the processes: -l 1:0,4:100. What happens
now? Does switching the order matter? Why? (As always, use -c
and -p to see if you were right)

```
Yes, because when it's IO first, CPU doesn't schedule anything we won't be seeing anything that is READY, therefore 
once PID 0 is done we won't see other processes. 

```
4. We’ll now explore some of the other flags. One important flag is
-S, which determines how the system reacts when a process issues
an I/O. With the flag set to SWITCH ON END, the system
will NOT switch to another process while one is doing I/O, instead
waiting until the process is completely finished. What happens
when you run the following two processes (-l 1:0,4:100
-c -S SWITCH ON END), one doing I/O and the other doing CPU
work?

```
SWITCH ON END
The CPU only switches to another process when the current process is completely finished (either done with all its work or waiting for I/O).

If a process starts I/O, the CPU waits until the I/O is done instead of switching to another process.

```

```
python process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          
 11           DONE       RUN:cpu             1   

```


5. Now, run the same processes, but with the switching behavior set
to switch to another process whenever one isWAITING for I/O (-l
1:0,4:100 -c -S SWITCH ON IO).What happens now? Use -c
and -p to confirm that you are right.

```
python process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO 
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1   

```

```
SWITCH ON IO
If a process starts I/O, the CPU immediately switches to another process instead of waiting.

This helps keep the CPU busy while I/O is happening in the background.
```

6. One other important behavior is what to do when an I/O completes.
With -I IO RUN LATER, when an I/O completes, the process
that issued it is not necessarily run right away; rather, whatever
was running at the time keeps running. What happens when
you run this combination of processes? (./process-run.py -l
3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I
IO RUN LATER) Are system resources being effectively utilized?


```
python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_LATER
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1          
  8          READY          DONE       RUN:cpu         READY             1          
  9          READY          DONE       RUN:cpu         READY             1          
 10          READY          DONE       RUN:cpu         READY             1          
 11          READY          DONE       RUN:cpu         READY             1          
 12          READY          DONE          DONE       RUN:cpu             1          
 13          READY          DONE          DONE       RUN:cpu             1          
 14          READY          DONE          DONE       RUN:cpu             1          
 15          READY          DONE          DONE       RUN:cpu             1          
 16          READY          DONE          DONE       RUN:cpu             1          
 17    RUN:io_done          DONE          DONE          DONE             1          
 18         RUN:io          DONE          DONE          DONE             1          
 19        BLOCKED          DONE          DONE          DONE                           1
 20        BLOCKED          DONE          DONE          DONE                           1
 21        BLOCKED          DONE          DONE          DONE                           1
 22        BLOCKED          DONE          DONE          DONE                           1
 23        BLOCKED          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1          
 25         RUN:io          DONE          DONE          DONE             1          
 26        BLOCKED          DONE          DONE          DONE                           1
 27        BLOCKED          DONE          DONE          DONE                           1
 28        BLOCKED          DONE          DONE          DONE                           1
 29        BLOCKED          DONE          DONE          DONE                           1
 30        BLOCKED          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)

```

```
Becasue we did  IO_RUN_LATER
PID 0 is the process using IO, once starts to do that the CPU will finish up any other process
that is currently READT (PID 1, PID 2, PID 3) then goes back to PID 0 and finish UP the IO process.

This could cause a delay in IO, and if other process require the IO data from PID 0, it could cause 
inconistent data or system failure due to dependency.

```

7. Now run the same processes, but with -I IO RUN IMMEDIATE set,
which immediately runs the process that issued the I/O. How does
this behavior differ? Why might running a process that just completed
an I/O again be a good idea?

```
python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_IMMEDIATE
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1          
  8         RUN:io          DONE         READY         READY             1          
  9        BLOCKED          DONE       RUN:cpu         READY             1             1
 10        BLOCKED          DONE       RUN:cpu         READY             1             1
 11        BLOCKED          DONE       RUN:cpu         READY             1             1
 12        BLOCKED          DONE       RUN:cpu         READY             1             1
 13        BLOCKED          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1          
 15         RUN:io          DONE          DONE         READY             1          
 16        BLOCKED          DONE          DONE       RUN:cpu             1             1
 17        BLOCKED          DONE          DONE       RUN:cpu             1             1
 18        BLOCKED          DONE          DONE       RUN:cpu             1             1
 19        BLOCKED          DONE          DONE       RUN:cpu             1             1
 20        BLOCKED          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)

```

``` In IO_RUN_IMMEDIATE, when an I/O completes, the process that requested the I/O immediately gets CPU time. 
This ensures that the process can quickly continue its execution ```



SUMMARY ON 6 and 7:

In IO_RUN_LATER, when an I/O completes, the process that requested the I/O does not immediately run. Instead, whatever process was currently running on the CPU continues. This can lead to delays in handling I/O results, causing inefficiencies in CPU utilization.

In IO_RUN_IMMEDIATE, when an I/O completes, the process that requested the I/O immediately gets CPU time. This ensures that the process can quickly continue its execution, leading to better resource utilization and reduced idle time.

Key Observations from Your Results
Total Time Decreased

IO_RUN_LATER: 31 cycles

IO_RUN_IMMEDIATE: 21 cycles

The system finished execution 10 cycles faster when I/O processes were prioritized immediately.

CPU Utilization Improved

IO_RUN_LATER: 67.74% CPU busy

IO_RUN_IMMEDIATE: 100% CPU busy

No CPU cycles were wasted when switching to I/O processes immediately.

I/O Busy Time Remains Almost the Same

Both scenarios have 15 cycles of I/O work.

The difference is in how quickly the I/O results are processed.

Conclusion
IO_RUN_IMMEDIATE is more efficient because it reduces idle time and keeps both the CPU and I/O fully utilized.

IO_RUN_LATER introduces delays, but only affects performance, not correctness, unless another process depends on the I/O result.

In systems where fast response to I/O is important, IO_RUN_IMMEDIATE is preferred.





