CFLAGS=-c -Wall

sfind: main.o sfind.o
	gcc -o sfind main.o sfind.o

main.o: main.c
	    gcc -c main.c

sfind.o: sfind.c
	    gcc -c sfind.c

clean:
	    rm *o sfind
