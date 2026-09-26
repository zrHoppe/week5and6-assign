CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2 -fPIC
LIB_NAME = libvector.so
TARGET = test_shared
PREFIX ?= /usr/local

all: $(LIB_NAME) $(TARGET)

$(LIB_NAME): vector.o
	$(CC) -shared -o $@ $^

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c -o vector.o

$(TARGET): test.o $(LIB_NAME)
	$(CC) test.o -L. -lvector -Wl,-rpath,. -o $(TARGET)

test.o: test.c vector.h
	$(CC) -Wall -Wextra -pedantic -std=c11 -c test.c -o test.o

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

install: $(LIB_NAME)
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 755 $(LIB_NAME) $(PREFIX)/lib/
	install -m 644 vector.h $(PREFIX)/include/
	ldconfig || true

clean:
	rm -f *.o *.so $(TARGET)

.PHONY: all run valgrind install clean