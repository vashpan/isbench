INCLUDES = -I "../../src"
SRC = ../../src/*.c ../../src/platform/unix/*.c
CFLAGS = -std=c89
LDFLAGS = -static

MINGW64_CC = x86_64-w64-mingw32-gcc  # 64-bit compiler
MINGW32_CC = i686-w64-mingw32-gcc    # 32-bit compiler

all: isbench32-mingw isbench64-mingw isbench32-mingw-dbg isbench64-mingw-dbg

isbench32-mingw: $(SRC)
	$(MINGW32_CC) -o $@.exe $(SRC) -O2 $(CFLAGS) $(INCLUDES) $(LDFLAGS)

isbench64-mingw: $(SRC)
	$(MINGW64_CC) -o $@.exe $(SRC) -O2 $(CFLAGS) $(INCLUDES) $(LDFLAGS)

isbench32-mingw-dbg: $(SRC)
	$(MINGW32_CC) -o $@.exe $(SRC) -g $(CFLAGS) $(INCLUDES) $(LDFLAGS)

isbench64-mingw-dbg: $(SRC)
	$(MINGW64_CC) -o $@.exe $(SRC) -g $(CFLAGS) $(INCLUDES) $(LDFLAGS)

clean:
	rm -rf *.o isbench32-mingw.exe isbench64-mingw.exe isbench32-mingw-dbg.exe isbench64-mingw-dbg.exe
