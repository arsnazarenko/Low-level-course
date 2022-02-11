#include <stdio.h>

volatile int g = 2;
extern volatile int f;
static volatile int k = 1;

void method() {
    printf("lib: %p -> %d\n", &g, g);
    printf("lib: %p -> %d\n", &f, f);
    printf("lib: %p -> %d\n", &k, k);
}
