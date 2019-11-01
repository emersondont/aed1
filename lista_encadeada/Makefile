
all: main.o funcoes.o
	gcc main.o funcoes.o -o executavel

main.o: main.c
	gcc -c main.c

funcoes.o: funcoes.c
	gcc -c funcoes.c

clean:
	rm *.o executavel
