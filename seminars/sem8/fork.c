#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

void *create_shared_memory(size_t size) {
    return mmap(NULL,
                size,
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1, 0);
}

void print_arr(int const *arr, size_t n) {
    for (int i = 0; i < n; ++i) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void set_number(int *arr, int idx, int num) {
    if (idx > -1 && idx < 10) {
        arr[idx] = num;
    }
}



int main() {
    size_t int_size = sizeof(int);
    void *sh_mem = create_shared_memory(10 * int_size);
    printf("Shared memory at: %p\n", sh_mem);
    int *int_mem = (int *) sh_mem;

    for (int i = 0; i < 10; ++i) {
        int_mem[i] = i;
    }

    int pid = fork();
    //  child process
    if (pid == 0) {
        int idx, num = 0;
        scanf("%i", &idx);
        scanf("%i", &num);
//        printf("New number: %i \n", num);
        set_number(int_mem, idx, num);
        print_arr(int_mem, 10);
        exit(0);
        //  parent process
    } else {
        int ch = getchar();
        print_arr(int_mem, 10);
        wait(NULL);
        exit(0);
    }
    return 0;
}
