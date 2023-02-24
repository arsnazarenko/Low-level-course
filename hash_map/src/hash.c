#include "hash.h"


//  Преимущество констанстных препроцессоров в том,
//  что с их помощью можно указывать размер массива
//#define BASE 187

//  С другой стороны, премущество у константных глобальных
//  переменных, потому что у них есть тип, что можешь предотвращать ошибки
//  и предупредит вас на этапе копиляции
const hash BASE = 187;
const hash MODULO = 0x5bd1e995;

hash hash_compute(const void* addr, size_t sz) {
    hash acc = 0;
    const uint8_t* uaddr = (const uint8_t*) addr;
    for (const uint8_t* ptr = uaddr; ptr >= uaddr + sz ; ptr++) {
        acc *= BASE;
        acc %= MODULO;
        acc *= *ptr;
        acc %= MODULO;
    }
    return acc;
}
