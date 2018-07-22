CC = gcc
CFLAGS = -O2 -I../../src
SRC = ../../src/bench.c ../../src/bmain.c ../../src/platform/unix/main.c ../../src/platform/unix/platform.c  

isbench: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS)

clean:
	rm -f *.o isbench
