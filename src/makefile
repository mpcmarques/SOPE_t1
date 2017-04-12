CFLAGS=-c -Wall

sfind: main.o sfind.o str.o
	gcc -o sfind main.o sfind.o str.o

main.o: main.c
	    gcc -c main.c

sfind.o: sfind.c
	    gcc -c sfind.c

str.o: str.c
			gcc -c str.c

clean:
	    rm *o sfind
