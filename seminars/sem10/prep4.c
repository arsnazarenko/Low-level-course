#include <stdio.h>
#include <inttypes.h>

#define test(type, name, x) type##_print_##name(x)

void int64_t_print_int(int64_t i) { printf("%" PRId64 " hello\n", i); };
void int64_t_print_char(int64_t i) { printf("%" PRId64 " bye\n", i); };


void double_print_int(double i) { printf("%lf hello\n", i); };
void double_print_char(double i) { printf("%lf bye\n", i); };



int main() {
    int64_t a = 123;
    double t = 1.666;

    test(int64_t, int, a);
    
    test(int64_t, char, a);
    
    test(double, int, t);
    test(double, char, t);

    return 0;
}
