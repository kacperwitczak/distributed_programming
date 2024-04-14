run:
	
	gcc -Wall -I. -c template.c -o template.o
	gcc template.o -L. libpqueue.a -o template
	./template

clean:
	rm -f template template.o *.dat
