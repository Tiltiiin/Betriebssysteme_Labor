CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = memory_violation_demo

all: $(TARGET)

$(TARGET): memory_violation_demo.c
	$(CC) $(CFLAGS) -o $(TARGET) memory_violation_demo.c

clean:
	rm -f $(TARGET)

.PHONY: all clean 