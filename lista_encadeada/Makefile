
all: main.o funcoes.o ordenacao.o
	gcc main.o funcoes.o ordenacao.o -o executavel

main.o: main.c
	gcc -c main.c

funcoes.o: funcoes.c
	gcc -c funcoes.c

ordenacao.o: ordenacao.c
	gcc -c ordenacao.c

clean:
	rm *.o executavel
