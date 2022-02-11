#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void error(char const* s) {
    fprintf(stderr, "%s", s);
    abort();
}

#define _print(type, x) type##_print(x)

#define print(x)                                 \
    _Generic((x),                                \
        int64_t : int64_t_print(x),              \
        double : double_print(x),                \
        default : error("Unsupported operation") \
    )


void int64_t_print(int64_t i) { printf("%" PRId64, i); }
void double_print(double d) { printf("%lf", d); }
void print_newline() { puts(""); }

int main() {
    int64_t x = 42;
    double d = 99.99;
    print(x);
    print_newline();
    print(d);
    return 0;
}
