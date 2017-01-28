LIBS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf -std=gnu99
INCLUDE = -Iinclude/
SRC = src/player.c src/graphics.c src/main.c
TARGET = -o tabletop
GCC = gcc
all: main

main:
	$(GCC) $(TARGET) $(SRC) $(INCLUDE) $(LIBS)
