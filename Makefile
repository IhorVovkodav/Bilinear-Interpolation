.PHONY: all clean

CC:=gcc
CFLAGS+=-Wall -Wextra -std=c11 -Wpedantic

all: main

main: main_func.c basic_scale.o scale_intrinsics.o scale.S functions.o
	$(CC) $(CFLAGS) -c functions.c -O3
	$(CC) $(CFLAGS) -c basic_scale.c -O3
	$(CC) $(CFLAGS) -c scale_intrinsics.c -O3
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf main basic_scale.o scale_intrinsics.o functions.o
