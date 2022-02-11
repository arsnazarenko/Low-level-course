extern volatile int g;


/*  extern for function declaration means that
    the dependency will be resolved dynamically
*/
extern void method();

int main() {
    g++;
    method();
    while(1);
    return 0;
}


