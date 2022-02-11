#include <stdio.h>

#define print_var(x) printf(#x " is %d\n", x );

int main() {
    
    int a = 10;

    print_var(a);

    print_var(123);
    return 0;
}
