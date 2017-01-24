

all: main

main:
	gcc -o tabletop src/graphics.c src/main.c -Iinclude/ -lm -lSDL2 -lSDL2_image -lSDL2_ttf -std=gnu99
