#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>

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

void print_number(int const* arr, int idx) {
    if (idx > -1 && idx < 10) {
        printf("%i\n", arr[idx]);
    }
}



int main() {
    size_t int_size = sizeof(int);
    void *sh_mem = create_shared_memory(10 * int_size);
    printf("Shared memory at: %p\n", sh_mem);
    int *int_mem = (int *) sh_mem;
    pthread_barrier_t* sh_mem_barrier = (pthread_barrier_t*) create_shared_memory(sizeof(pthread_barrier_t));
    pthread_barrierattr_t attr;
    pthread_barrierattr_init(&attr);
    pthread_barrierattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_barrier_init(sh_mem_barrier, &attr, 2);

    for (int i = 0; i < 10; ++i) {
        int_mem[i] = i;
    }

    int pid = fork();
    //  child process
    if (pid == 0) {
        time_t now;
        char buf[27];
        time(&now);
        printf("Child process starting at %s", ctime_r (&now, buf));
        int idx = 0;
        pthread_barrier_wait(sh_mem_barrier);
        scanf("%i", &idx);
        print_number(int_mem, idx);
        print_arr(int_mem, 10);
        time(&now);
        printf ("Child process done at %s", ctime_r (&now, buf));

        //  parent process
    } else {
        time_t now;
        char buf[27];
        time(&now);
        printf("Parent process starting at %s", ctime_r (&now, buf));
        print_arr(int_mem, 10);
        int idx, num = 0;
        scanf("%i", &idx);
        scanf("%i", &num);
        set_number(int_mem, idx, num);
        // do the computation...
        sleep(5);
        pthread_barrier_wait(sh_mem_barrier);
        time(&now);
        wait(NULL);
        pthread_barrierattr_destroy(&attr);
        pthread_barrier_destroy(sh_mem_barrier); 
        printf ("Parent process done at %s", ctime_r (&now, buf));
    }
    return 0;
}

