volatile int f = 0;

extern volatile int g;

static volatile int h = 1;

extern void method();
int main() {
    g++;
    f++;
    h++;
    method();
    for(;;);
    return 0;
}
