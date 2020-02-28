INPUT=./in/test4.in
OUTPUT=./out.txt

FLAGS=-Wall -Wextra

build:	tema2.o aux.o Operatii.o Coada.o Stiva.o
	gcc $(FLAGS) $^ -o tema2

tema2.o:	tema2.c
	gcc $(FLAGS) -c $^ -o $@

aux.o:	aux.c
	gcc $(FLAGS) -c $^ -o $@

Operatii.o:	Operatii.c
	gcc $(FLAGS) -c $^ -o $@

Coada.o:	Coada.c
	gcc $(FLAGS) -c $^ -o $@

Stiva.o:	Stiva.c
	gcc $(FLAGS) -c $^ -o $@

run:	tema2
	./tema2 $(INPUT) $(OUTPUT)
	rm -rf *.o

clean:
	rm -rf *.o tema2
