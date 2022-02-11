#include <stdio.h>


//  definition of variable in dyn. library
volatile int g = 0;

//  definition of function in dyn. library
void method() {
    printf("lib: %p -> %d\n", &g, g);
}
