#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "base.h"

void print(uintptr_t value) {
    printf("%" PRIdPTR "\n", value);
}

int main() {
    interpreter();
}
