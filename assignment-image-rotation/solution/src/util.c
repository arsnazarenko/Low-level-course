#include "util.h"
#include <stdio.h>


void app_err(const char* str) {
    fputs(str, stderr);
    fputs("\n", stderr);
}

void app_log(const char* str) {
    fputs(str, stdout);
    fputs("\n", stdout);
}
