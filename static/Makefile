CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2
AR = ar
ARFLAGS = rcs
LIB_NAME = libvector.a
TARGET = test_static
PREFIX ?= /usr/local

all: $(LIB_NAME) $(TARGET)

$(LIB_NAME): vector.o
	$(AR) $(ARFLAGS) $@ $^

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c -o vector.o

$(TARGET): test.o $(LIB_NAME)
	$(CC) $(CFLAGS) test.o -L. -lvector -o $(TARGET)

test.o: test.c vector.h
	$(CC) $(CFLAGS) -c test.c -o test.o

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

install: $(LIB_NAME)
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 644 $(LIB_NAME) $(PREFIX)/lib/
	install -m 644 vector.h $(PREFIX)/include/

clean:
	rm -f *.o *.a $(TARGET)

.PHONY: all run valgrind install clean