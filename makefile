all: ./src/main.c
	c99 -g src/*.c -o ./bin/filter

clear:
	rm -f ./bin/filter