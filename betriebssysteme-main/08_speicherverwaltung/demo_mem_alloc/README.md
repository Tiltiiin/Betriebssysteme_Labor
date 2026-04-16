# Linux Memory Allocation Demo

## Overview
This demo program illustrates different types of memory allocation in Linux and their effects on system memory. It's designed to help students understand how memory is managed at both the process and system level.

## Learning Objectives
- Understand different types of memory allocation (stack, heap, mmap)
- Learn how to monitor memory usage using system tools
- Observe copy-on-write behavior in Linux
- Understand memory pressure and its effects
- Learn to interpret memory-related system metrics

## Prerequisites
- Linux operating system
- GCC compiler
- Basic understanding of C programming
- System monitoring tools (htop, vmstat, pmap)

## Required Tools
```bash
# Install required tools on Ubuntu/Debian
sudo apt-get install htop sysstat

# On Fedora/RHEL
sudo dnf install htop sysstat
```

## Building the Demo
```bash
# Compile the program
make

# Clean build files
make clean
```

## Running the Demo

1. **Start the monitoring tools** in separate terminals:

Terminal 1 (htop):
```bash
htop
```

Terminal 2 (vmstat):
```bash
vmstat 1
```

Terminal 3 (pmap):
```bash
# Get the process ID after starting the program
pmap -x $(pgrep memory_demo)
```

2. **Run the demo program**:
```bash
./memory_demo
```

## Demo Stages and What to Observe

### 1. Initial State
- Observe the baseline memory usage
- Note the process's initial memory footprint
- Check the system's free memory

### 2. Stack Allocation (1MB)
- Watch the process's memory usage increase
- In pmap, look for the stack segment
- Note that stack memory is limited and fixed-size

### 3. Heap Allocation (100MB)
- Observe the significant increase in memory usage
- In pmap, identify the [heap] segment
- Note the difference between virtual and physical memory usage

### 4. Memory Mapping (100MB)
- Watch for the new anonymous mapping in pmap
- Compare with heap allocation behavior
- Note the different memory management approach

### 5. Copy-on-Write Demonstration
- Observe the child process creation
- Watch how memory is shared between parent and child
- See the copy-on-write behavior when the child modifies memory

### 6. Memory Pressure Test
- Watch the system's response to increasing memory usage
- Observe swap usage in vmstat
- Note when the system starts to show memory pressure

### 7. Cleanup
- Observe memory being freed
- Watch the process's memory footprint decrease
- Note any remaining memory allocations

## Key Concepts to Understand

### Memory Types
1. **Stack Memory**
   - Fixed size
   - Automatic allocation/deallocation
   - Limited by system constraints

2. **Heap Memory**
   - Dynamic allocation
   - Manual management (malloc/free)
   - More flexible but requires careful management

3. **Memory Mapping**
   - Direct mapping to physical memory
   - Can be shared between processes
   - Used for large allocations

### System Tools
1. **htop**
   - Process-level memory usage
   - System-wide memory statistics
   - Real-time monitoring

2. **vmstat**
   - System-wide memory statistics
   - Swap usage
   - Memory pressure indicators

3. **pmap**
   - Detailed memory mapping
   - Virtual memory layout
   - Memory segment information

## Common Questions

1. **Why does the process use more virtual memory than physical memory?**
   - Linux uses virtual memory management
   - Physical memory is allocated on demand
   - Copy-on-write optimization

2. **What happens during the memory pressure test?**
   - System starts using swap
   - Memory allocation becomes slower
   - Eventually, allocation fails

3. **Why does the child process share memory with the parent?**
   - Copy-on-write optimization
   - Memory is only copied when modified
   - Efficient memory usage

## Further Reading
- Linux Memory Management Documentation
- Understanding the Linux Virtual Memory Manager
- Linux System Programming by Robert Love

## Troubleshooting

If you encounter issues:
1. Ensure you have sufficient memory available
2. Check if all required tools are installed
3. Verify you have appropriate permissions
4. Check system logs for memory-related messages

## Contributing
Feel free to modify the demo program to explore additional memory concepts or add new features.

## License
This project is licensed under the MIT License - see the LICENSE file for details. 