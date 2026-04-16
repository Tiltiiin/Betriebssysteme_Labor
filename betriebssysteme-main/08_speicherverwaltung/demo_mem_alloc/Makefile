CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = memory_demo

all: $(TARGET)

$(TARGET): memory_demo.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) 