# Virtual Memory Simulation

## Overview

This program demonstrates virtual memory behavior by allocating a large 2GB memory block and performing both sequential and random memory access patterns. It measures access times to observe how the operating system handles memory management, including swapping behavior when memory usage exceeds available physical RAM.

The program is designed to help understand the performance differences between sequential and random memory access patterns and how virtual memory systems respond under memory pressure.

## Build & Run
```bash
# Clone the repo
git clone https://github.com/AniDashyan/virtual_memory_simulation/
cd virtual_memory_simulation

# Build the projec
cmake -S . -B build
cmake --build build

# Run the executable:
./build/main
```

## Example Output

```
Virtual Memory Demonstration Program
====================================
This program will allocate 2 GB of memory
and demonstrate virtual memory behavior.

Allocating 2 GB of memory...
Memory allocation successful!
Memory allocated at address: 0x26627507040

=== Sequential Memory Access Test ===
Accessing 2048 MB sequentially...
Sequential iteration 0 completed
Sequential iteration 1000 completed
Sequential iteration 2000 completed
Sequential iteration 3000 completed
Sequential iteration 4000 completed
Sequential iteration 5000 completed
Sequential iteration 6000 completed
Sequential iteration 7000 completed
Sequential iteration 8000 completed
Sequential iteration 9000 completed
Sequential access completed in 139391 ms
Average time per iteration: 13.9391 ms

=== Random Memory Access Test ===
Performing 10000 random accesses...
Random iteration 0 completed
Random iteration 1000 completed
Random iteration 2000 completed
Random iteration 3000 completed
Random iteration 4000 completed
Random iteration 5000 completed
Random iteration 6000 completed
Random iteration 7000 completed
Random iteration 8000 completed
Random iteration 9000 completed
Random access completed in 2 ms
Average time per access: 0.0002 ms
Memory deallocated. Program complete.
```

## How Does It Work?

The program allocates 2GB of virtual memory and performs two access patterns:

1. **Sequential Access**: Writes to memory in 4KB chunks sequentially, demonstrating good spatial locality
2. **Random Access**: Accesses random memory locations, showing poor spatial locality

Both patterns measure execution time to reveal virtual memory behavior. When physical RAM is exceeded, we'll observe increased access times due to swapping (monitor with `htop`, `vmstat`, or Task Manager).
