INCLUDES = -I "../../src"
SRC = ../../src/*.c	../../src/platform/unix/*.c
CFLAGS = -std=c89

isbench: $(SRC)
	$(CC) -o $@ $(SRC) -O2 $(CFLAGS) $(INCLUDES)

isbench-dbg: $(SRC)
	$(CC) -o $@ $(SRC) -g $(CFLAGS) $(INCLUDES)

clean:
	rm -rf *.o isbench isbench-dbg isbench-dbg.dSYM	
