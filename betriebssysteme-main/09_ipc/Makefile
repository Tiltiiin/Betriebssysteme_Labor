# This program is free to use for educational purposes but is not allowed
# to be shared outside the course "Betriebsysteme" at Esslingen University.
# Author: Dennis Grewe
# Date: 16.11.2024
# Makefile for compiling semaphore, signals, message queue, pipe, fifo, and socket programs

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -lpthread

# Source files
SOURCES = semaphore.c signals.c shared_mem.c message_queue.c pipe.c fifo.c socket.c

# Executable names
EXECUTABLES = semaphore signals shared_mem message_queue pipe fifo socket

# Default target
all: $(EXECUTABLES)

# Rule to compile semaphore
semaphore: semaphore.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile signals
signals: signals.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile shared memory
shared_mem: shared_mem.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile message queue
message_queue: message_queue.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile pipe
pipe: pipe.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile fifo
fifo: fifo.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile socket
socket: socket.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove compiled binaries
clean:
	rm -f $(EXECUTABLES)

.PHONY: all clean
