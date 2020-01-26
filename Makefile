
CFLAGS = -Wall -pedantic -g -Og -std=c99

TARGET = cdraw

all: $(TARGET) libcdraw.so

$(TARGET): test.o list.o cdraw.o
	gcc $(CFLAGS) test.o -L. -lcdraw -o $(TARGET)

test.o: test.c
	gcc $(CFLAGS) -c test.c

libcdraw.so: cdraw.o list.o
	gcc $(CFLAGS) -shared cdraw.o list.o -o libcdraw.so

cdraw.o: cdraw.c cdraw.h
	gcc $(CFLAGS) -fPIC -c cdraw.c

list.o: list.c list.h
	gcc $(CFLAGS) -fPIC -c list.c

clean:
	rm *.o $(TARGET) libcdraw.so
