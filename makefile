all : run

run : clean
	./programme

clean : build
	rm -f *.o*
	
build : main.o clientAPI.o
	gcc -o programme main.o clientAPI.o snakeAPI.o mysnake.o arbre.o annex.o file.o

main.o : main.c
	gcc -o main.o -c main.c

clientAPI.o : gameInterface/clientAPI.c snakeAPI.o
	gcc -o clientAPI.o -c gameInterface/clientAPI.c
	
snakeAPI.o : gameInterface/snakeAPI.c mysnake.o
	gcc -o snakeAPI.o -c gameInterface/snakeAPI.c

mysnake.o : mySnake/mySnake.c arbre.o
	gcc -o mysnake.o -c mySnake/mySnake.c

arbre.o : mySnake/arbre.c annex.o
	gcc -o arbre.o -c mySnake/arbre.c

annex.o : mySnake/annex.c file.o
	gcc -o annex.o -c mySnake/annex.c

file.o : mySnake/file.c
	gcc -o file.o -c mySnake/file.c