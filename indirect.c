#include <stdint.h>
#include <stdlib.h>

#include "base.h"

typedef void (*codeptr)(void);

struct object {
    codeptr code;
    const struct object *payload[];
};

// Primitives

void code_one(void);
const struct object o_one = { .code = code_one };

void code_add(void);
const struct object o_add = { .code = code_add };

void code_print(void);
const struct object o_print = { .code = code_print };

void code_exit(void);
const struct object o_exit = { .code = code_exit };

void code_return(void);
const struct object o_return = { .code = code_return };

// Complex subroutines

void code_subroutine(void);

const struct object o_two = {
    .code = code_subroutine,
    .payload = { &o_one, &o_one, &o_add, &o_return },
};

const struct object o_four = {
    .code = code_subroutine,
    .payload = { &o_two, &o_two, &o_add, &o_return },
};

const struct object o_main = {
    .code = code_subroutine,
    .payload = { &o_four, &o_print, &o_exit },
};

const struct object *const start = &o_main;

const struct object *const *ip = &start;

uintptr_t stack_buf[STACK_SIZE];
uintptr_t *sp = stack_buf;

const struct object *const *rstack_buf[STACK_SIZE];
const struct object *const **rsp = rstack_buf;

void interpreter(void) {
    for (;;)
        (*ip)->code();
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

void code_subroutine(void) {
    const struct object *self = *ip;
    ip++;
    *(rsp++) = ip;
    ip = self->payload;
}

void code_return(void) {
    ip = *(--rsp);
}
