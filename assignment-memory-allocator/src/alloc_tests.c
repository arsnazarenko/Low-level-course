#include <sys/mman.h>
#include "alloc_tests.h"
#include "util.h"

// simple allocations
static void first_test() {
    fputs("_____________________________________________________________\n", stdout);
    fputs("TEST 1 START:\n", stdout);
    MALLOC_AND_GET_HEADER(1, 300);
    MALLOC_AND_GET_HEADER(2, 200);
    MALLOC_AND_GET_HEADER(3, 350);
    debug_heap(stdout, h1);
    bool check1 = !h1->is_free;
    bool check2 = !h2->is_free;
    bool check3 = !h3->is_free;
    if (check1 && check2 && check3) {
        _free(m1);
        _free(m2);
        _free(m3);
        fputs("MEMORY AFTER FREE:\n", stdout);
        debug_heap(stdout, h1);
        fputs("TEST 1 PASSED\n", stdout);
    } else { err("TEST 1 FAILED\n"); }
}
// allocations and one free
static void second_test() {
    fputs("_____________________________________________________________\n", stdout);
    fputs("TEST 2 START:\n\n", stdout);
    MALLOC_AND_GET_HEADER(1, 300);
    MALLOC_AND_GET_HEADER(2, 200);
    MALLOC_AND_GET_HEADER(3, 350);
    debug_heap(stdout, h1);
    fputs("free second block\n", stdout);
    _free(m2);
    debug_heap(stdout, h1);
    bool check1 = !h1->is_free;
    bool check2 = h2->is_free;
    bool check3 = !h3->is_free;
    if (check1 && check2 && check3) {
        _free(m1);
        _free(m3);
        fputs("MEMORY AFTER FREE:\n", stdout);
        debug_heap(stdout, h1);
        fputs("TEST 2 PASSED\n", stdout);
    } else { err("TEST 2 FAILED\n"); }
}

// allocations and two free
static void third_test() {
    fputs("_____________________________________________________________\n", stdout);
    fputs("TEST 3 START:\n", stdout);
    MALLOC_AND_GET_HEADER(1, 300);
    MALLOC_AND_GET_HEADER(2, 200);
    MALLOC_AND_GET_HEADER(3, 350);
    debug_heap(stdout, h1);
    fputs("free second and third blocks\n", stdout);
    _free(m2);
    _free(m3);
    debug_heap(stdout, h1);
    bool check1 = !h1->is_free;
    bool check2 = h2->is_free;
    bool check3 = h3->is_free;
    if (check1 && check2 && check3) {
        _free(m1);
        fputs("MEMORY AFTER FREE:\n", stdout);
        debug_heap(stdout, h1);
        fputs("TEST 3 PASSED\n", stdout);
    } else { err("TEST 3 FAILED\n"); }
}
// allocations for two regions side by side
static void fourth_test() {
    fputs("_____________________________________________________________\n", stdout);

    fputs("TEST 4 START:\n", stdout);
    fputs("One memory region\n", stdout);
    MALLOC_AND_GET_HEADER(1, 5000);
    debug_heap(stdout, h1);
    // address above first block
    void* after_first_block = (h1->contents + h1->capacity.bytes);
    fputs("Two memory regions side by side\n", stdout);
    MALLOC_AND_GET_HEADER(2, 5000);
    debug_heap(stdout, h1);
    bool check1 = !h1->is_free;
    bool check2 = !h2->is_free;
    bool check3 = ((void*) h2 == after_first_block);
    if (check1 && check2 && check3) {
        _free(m1);
        _free(m2);
        fputs("MEMORY AFTER FREE:\n", stdout);
        debug_heap(stdout, h1);
        fputs("TEST 4 PASSED\n", stdout);
    } else { err("TEST 4 FAILED\n"); }
}

// allocations for two regions not side by side
static void fifth_test() {
    fputs("_____________________________________________________________\n", stdout);
    fputs("TEST 5 START:\n", stdout);
    fputs("One memory region\n", stdout);
    MALLOC_AND_GET_HEADER(1, 10000);
    debug_heap(stdout, h1);
    struct block_header* last = h1;
    // find last block in heap
    while(last->next) {
        last = last->next;
    }
    // address after last heap block
    void* addr = (last->contents + last->capacity.bytes);
    // create memory
    void* some_mem = mmap(addr, 2000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    // malloc new region
    MALLOC_AND_GET_HEADER(2, 7000);
    fputs("Two memory regions are not side by side\n", stdout);
    debug_heap(stdout, h1);
    bool check1 = !h1->is_free;
    bool check2 = !h2->is_free;
    //  start of new region must not be after first region
    bool check3 = (void*) last->next != some_mem;
    if (check1 && check2 && check3) {
        _free(m1);
        _free(m2);
        fputs("MEMORY AFTER FREE:\n", stdout);
        debug_heap(stdout, h1);
        fputs("TEST 5 PASSED\n", stdout);
    } else { err("TEST 5 FAILED\n"); }
}


void run_all_tests() {
    heap_init(HEAP_SIZE_TEST);
    first_test();
    second_test();
    third_test();
    fourth_test();
    fifth_test();
}