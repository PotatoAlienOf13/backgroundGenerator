all: bgg.c
	gcc -g -Wall -o bgg bgg.c -lm -lcairo  
