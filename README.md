# Linux Process and Thread Examples

This repository contains sample C and C++ programs related to Linux processes and threads.

The examples accompany my blog article:

## Topics Covered

- Linux Processes
- Linux Threads
- POSIX Threads (pthreads)
- Thread Scheduling Policies
- Thread Priorities
- Thread Synchronization
- Mutexes
- Semaphores
- Condition Variables
- Thread Cleanup Handlers
- Thread Cancellation

## Files

| File | Description |
|--------|-------------|
| thread_sample.c | POSIX thread example |
| cpp_thread_sample.cpp | C++ thread example |

## Build

### C Example - Thread sample

```bash
gcc thread_sample.c -o thread_sample -lpthread
run: ./thread_sample

### C++ Example - Thread sample
g++ cpp_thread_sample.cpp -o cpp_thread_sample -pthread
run: ./cpp_thread_sample
