
all: main.o funcoes.o
	gcc main.o funcoes.o -o executavel

funcoes.o: funcoes.c
	gcc -c funcoes.c

main.o: main.c
	gcc -c main.c

clean:
	rm *.o executavel
