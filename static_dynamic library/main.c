/* Distributed Programming
   Lab2 - libraries - example

   (C) by Mariusz Matuszek
   Gdańsk University of Technology
*/


// main app

#include "types.h"
#include "functions.h"
#include <stdio.h>


int main(int argc, char* argv[]) {

  data_t x, y;

  x.a = x.b = y.a = y.b = 1;

  printf("wynik dodawania: %d\n", add(x, y));

  return 0;
}
