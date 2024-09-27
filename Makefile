ComFlag = gcc
CFLAGS = -I ./include
LFLAGS = -L ./lib -l mingw32 -l SDL2main -l SDL2

all: main

main: main.c
	$(ComFlag) $(CFLAGS) -o main main.c $(LFLAGS)

clean:
	rm -f main
