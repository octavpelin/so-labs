CC = gcc
CFLAGS = -Wall
LDLIBS = -DHAVE_MATH -lm

all: ops

ops: ops.o mul.o add.o
	$(CC) $(CFLAGS) -o $@ $? $(LDLIBS)

ops.o: ops.c
	$(CC) $(CFLAGS) -c $? $(LDLIBS)
mul.o: mul.c
add.o: add.c

clean:
	rm -rf *.o ops

