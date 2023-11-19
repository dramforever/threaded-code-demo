#include <stdint.h>
#include <stdlib.h>

#include "base.h"

typedef void (*codeptr)(uintptr_t);

struct instr {
    codeptr code;
    uintptr_t data;
};

void code_push(uintptr_t);
void code_add(uintptr_t);
void code_print(uintptr_t);
void code_exit(uintptr_t);

void code_subroutine(uintptr_t);
void code_return(uintptr_t);

const struct instr sr_three[] = {
    { .code = code_push, .data = 1 },
    { .code = code_push, .data = 2 },
    { .code = code_add },
    { .code = code_return },
};

const struct instr sr_six[] = {
    { .code = code_subroutine, .data = (uintptr_t) sr_three },
    { .code = code_subroutine, .data = (uintptr_t) sr_three },
    { .code = code_add },
    { .code = code_return },
};

const struct instr sr_main[] = {
    { .code = code_subroutine, .data = (uintptr_t) sr_six },
    { .code = code_print },
    { .code = code_exit },
};

const struct instr i_main = {
    .code = code_subroutine,
    .data = (uintptr_t) sr_main,
};

const struct instr *ip = &i_main;

uintptr_t stack_buf[STACK_SIZE];
uintptr_t *sp = stack_buf;

const struct instr *rstack_buf[STACK_SIZE];
const struct instr **rsp = rstack_buf;

void interpreter(void) {
    for (;;) {
        struct instr ins = *ip;
        ins.code(ins.data);
    }
}

void code_push(uintptr_t data) {
    ip++;
    *(sp++) = data;
}

void code_add(uintptr_t data) {
    ip++;
    uintptr_t b = *(--sp);
    uintptr_t a = *(--sp);
    *(sp++) = a + b;
}

void code_print(uintptr_t data) {
    ip++;
    uintptr_t val = *(--sp);
    print(val);
}

void code_exit(uintptr_t data) {
    ip++;
    exit(0);
}

void code_subroutine(uintptr_t data) {
    const struct instr *sr = (const struct instr *) data;
    ip++;
    *(rsp++) = ip;
    ip = sr;
}

void code_return(uintptr_t data) {
    ip = *(--rsp);
}
