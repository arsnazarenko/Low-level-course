#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SZ 10

typedef struct {
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
} shared_mutex;



typedef struct {
    shared_mutex* mutex;
    int* array;
} shared_memory;


void *create_shared_memory(size_t size) {
    return mmap(NULL,
                size,
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1, 0);
}

void print_arr(int const *arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void set_number(int *arr, int idx, int num) {
    if (idx > -1 && idx < SZ) {
        arr[idx] = num;
    }
}

void print_number(int const* arr, int idx) {
    if (idx > -1 && idx < SZ) {
        printf("%i\n", arr[idx]);
    }
}
/*
 * call in all processes, because in methods
 * pthread_mutex_init and pthread_mutexattr_init use
 * dynamically-allocated memory => this memory will alloc in parent and child process
*/
void sh_mutex_destroy(shared_mutex* sh_mutex) {
    pthread_mutex_destroy(&(sh_mutex->mutex));
    pthread_mutexattr_destroy(&(sh_mutex->attr));
}



void sh_mutex_init(shared_mutex* sh_mutex) {
    pthread_mutexattr_init(&(sh_mutex->attr));
    pthread_mutexattr_setpshared(&(sh_mutex->attr), PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&(sh_mutex->mutex), &(sh_mutex->attr));
}



int main() {
    void * shared = create_shared_memory(sizeof(shared_mutex) + SZ * sizeof(int));
    shared_mutex* mutex =  (shared_mutex*) shared;
    int* shared_array = (int*) (((char* ) shared) + sizeof(shared_mutex) );
    shared_memory sh_memory = {.mutex = mutex, .array = shared_array};
    printf("Shared memory at: %p\n", shared);
    sh_mutex_init(sh_memory.mutex);
    for (int i = 0; i < SZ; ++i) {
        sh_memory.array[i] = i + 1;
    }
    print_arr(sh_memory.array, SZ);
    int pid = fork();
    //  child process
    if (pid == 0) {
        time_t now;
        char buf[27];
        time(&now);
        printf("Child process starting at %s", ctime_r (&now, buf));
        pthread_mutex_lock(&(sh_memory.mutex->mutex));
        
        print_arr(sh_memory.array, SZ);
        pthread_mutex_unlock(&(sh_memory.mutex->mutex));
        time(&now);
        printf ("Child process done at %s", ctime_r (&now, buf));
        sh_mutex_destroy(sh_memory.mutex);
        
        exit(0);
    } else {
        time_t now;
        char buf[27];
        time(&now);
        printf("Parent process starting at %s", ctime_r (&now, buf));
        pthread_mutex_lock(&(sh_memory.mutex->mutex));
        for (int i = 0; i < SZ; ++i) {
            ++sh_memory.array[i];
        }
        pthread_mutex_unlock(&(sh_memory.mutex->mutex));
        time(&now);
        printf ("Parent process done at %s", ctime_r (&now, buf));
        wait(NULL);
        sh_mutex_destroy(sh_memory.mutex);
    }

    return 0;
}

