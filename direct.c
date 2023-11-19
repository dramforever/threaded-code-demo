#include <stdint.h>
#include <stdlib.h>

#include "base.h"

typedef void (*codeptr)(void);

void code_one(void);
void code_add(void);
void code_print(void);
void code_exit(void);

const codeptr program[] = {
    code_one, code_one, code_add, code_print, code_exit,
};

const codeptr *ip = program;

uintptr_t stack_buf[STACK_SIZE];
uintptr_t *sp = stack_buf;

void interpreter(void) {
    for (;;)
        (*ip)();
}

void code_one(void) {
    ip++;
    *(sp++) = 1;
}

void code_add(void) {
    ip++;
    uintptr_t b = *(--sp);
    uintptr_t a = *(--sp);
    *(sp++) = a + b;
}

void code_print(void) {
    ip++;
    uintptr_t val = *(--sp);
    print(val);
}

void code_exit(void) {
    ip++;
    exit(0);
}
