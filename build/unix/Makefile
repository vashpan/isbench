CC = gcc
CFLAGS = -I../../src
INCLUDES = -I "../../src"
SRC = ../../src/*.c ../../src/platform/unix/*.c

isbench: $(SRC)
	$(CC) -o $@ $(SRC) -O2 $(CFLAGS) $(INCLUDES)

isbench-dbg: $(SRC)
	$(CC) -o $@ $(SRC) -g $(CFLAGS) $(INCLUDES)

clean:
	rm -f *.o isbench	
