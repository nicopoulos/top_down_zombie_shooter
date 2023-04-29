CC = gcc
BUILDFLAGS = -std=c17 -Wall -Wextra -g -O0
RELEASEFLAGS = -std=c17
LIBS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


SOURCEFILES = Code/*.c Code/Engine/*.c

build:
	$(CC) $(BUILDFLAGS) $(SOURCEFILES) $(LIBS)

run:
	./a.out

release:
	$(CC) $(CFLAGS) $(SOURCEFILES) $(LIBS)