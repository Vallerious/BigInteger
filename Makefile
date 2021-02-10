CC=gcc
CFLAGS=-I -std=c++11
DEPS = BigInteger.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: TestDriver.o
	$(CC) -o TestDriver TestDriver.cpp