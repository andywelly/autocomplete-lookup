dict2: main.o array.o business.o print_functions.o read.o string_functions.o tree.o
	gcc -g -o dict2 main.o array.o business.o print_functions.o read.o string_functions.o tree.o

dict3: main.o tree.o business.o print_functions.o read.o string_functions.o array.o
	gcc -g -o dict3 main.o tree.o business.o print_functions.o read.o string_functions.o array.o

main.o: main.c array.h business.h print_functions.h read.h string_functions.h

array.o: array.c array.h business.h print_functions.h string_functions.h

business.o: business.c business.h

print_functions.o: print_functions.c print_functions.h business.h

read.o: read.c read.h array.h tree.h

string_functions.o: string_functions.c string_functions.h

clean:
	rm -f dict2 dict3 *.o

