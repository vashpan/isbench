INCLUDES = -I "../../src" -I "../../src/bench"
SRC = ../../src/*.c ../../src/bench/*.c ../../src/platform/unix/*.c

isbench: $(SRC)
	$(CC) -o $@ $(SRC) -O2 $(CFLAGS) $(INCLUDES)

isbench-dbg: $(SRC)
	$(CC) -o $@ $(SRC) -g $(CFLAGS) $(INCLUDES)

clean:
	rm -rf *.o isbench isbench-dbg isbench-dbg.dSYM	
