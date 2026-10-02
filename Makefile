# CIS*2520 F26 Assignment 1 - Makefile
# Complete the four TODO items below. Every command line in a rule must
# start with a TAB (not spaces). Do not change the compiler or the flags.

CC = gcc
CFLAGS = -std=c99 -Wall -pedantic
TARGET = a1rental

SRCS = a1.c a1_functions.c
OBJS = a1.o a1_functions.o
all:$(TARGET)
#step 1
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

#step 2
a1.o:a1.c a1.h
	$(CC) $(CFLAGS) -c a1.c -o a1.o

#step 3
a1_functions.o:a1_functions.c a1.h
	$(CC) $(CFLAGS) -c a1_functions.c -o a1_functions.o

#step 4
clean:
	rm -f $(OBJS) $(TARGET) //clean up



# TODO 1: write the rule that links the object files ($(OBJS)) into $(TARGET).

# TODO 2: write the rule that compiles a1.c into a1.o.
#         Use $(CC) and $(CFLAGS). a1.o must be rebuilt when a1.c OR a1.h changes.

# TODO 3: write the rule that compiles a1_functions.c into a1_functions.o
#         (same idea as TODO 2).

# TODO 4: write the clean rule: remove the object files and the executable.

.PHONY: all clean
