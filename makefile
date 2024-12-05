all : run

run : clean
	./programme

clean : build
	rm -f *.o*

build : main.o clientAPI.o
	gcc -o programme main.o clientAPI.o snakeAPI.o

main.o : main.c
	gcc -o main.o -c main.c

clientAPI.o : clientAPI.c snakeAPI.o
	gcc -o clientAPI.o -c clientAPI.c
	
snakeAPI.o : snakeAPI.c
	gcc -o snakeAPI.o -c snakeAPI.c