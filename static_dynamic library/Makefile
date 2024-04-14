monolithic:
	gcc -Wall -c functions.c -o functions.o
	gcc -Wall -c main.c -o main.o
	gcc -Wall functions.o main.o -o program
	@echo "\n======================\nTesting monolithic\n======================"
	./program
	
static:
	gcc -Wall -c functions.c -o functions.o
	gcc -Wall -c main.c -o main.o
	ar r lib_functions.a functions.o
	ar tv lib_functions.a
	gcc main.o -L. -l_functions -o program_static
	@echo "\n======================\nTesting static library\n======================"
	./program_static

dynamic:
	gcc -Wall -c main.c -o main.o
	gcc -Wall -fPIC -c functions.c
	gcc functions.o -shared -o lib_functions.so
	gcc main.o -L. -l_functions -o program_dynamic
	@echo "\n=======================\nTesting dynamic library\n======================="
	ldd ./program_dynamic
	@echo "\nNow run: export LD_LIBRARY_PATH=\"....." && ./program_dynamic"
	
clean:
	rm -f *.o *.a *.so program program_static program_dynamic

all: monolithic static dynamic