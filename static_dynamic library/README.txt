Disclaimer!!!
Most of the code in this project is not mine. The code was provided to me for laboratory purposes. My task was to compile the code in various ways (makefile), test its functionality, and learn the differences between a static and dynamic library.

// Pattern for lab2
// Mariusz Matuszek

=========================
Testing as monolithic app
=========================

$ gcc -Wall -c functions.c -o functions.o
$ gcc -Wall -c main.c -o main.o
$ gcc main.o functions.o -o program

$ ./program


======================
Testing static library
======================

// create lib
$ ar r lib_functions.a functions.o

// list lib contents
$ ar tv lib_functions.a

// create and test app
$ gcc main.o lib_functions.a -o program_static
$ ./program_static


=======================
Testing dynamic library
=======================

// build lib
$ gcc -Wall -fPIC -c functions.c
$ gcc functions.o -shared -o lib_functions.so

// link app to lib
$ gcc main.o -L. -l_functions.so -o program_dynamic

// test what the app links to
$ ldd ./program_dynamic

// run app (will fail)
$ ./program_dynamic

// now app will run
$ export LD_LIBRARY_PATH=.:"$LD_LIBRARY_PATH"
$ ./program_dynamic



....

Have fun :-)
