all: main.o regression.o
	gcc -g -m64 -no-pie main.o regression.o

main.o:
	gcc -g -c -m64 ./src/main.c

regression.o:
	gcc -g -c -m64 ./src/regression.s

clean:
	rm ./main.o ./regression.o
