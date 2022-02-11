#include <stdio.h>
#include <unistd.h> 
int main() {
    for (size_t i = 0; i < 1000; ++i) {
        sleep(1);     
    }
    return 0;
}


