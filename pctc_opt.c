#include <stdint.h>
#include <stdlib.h>

#include "base.h"

struct instr;

#define DECL_STATE const struct instr *ip, uintptr_t *sp, const struct instr **rsp

#define STATE ip, sp, rsp

typedef void (*codeptr)(uintptr_t data, DECL_STATE);

struct instr {
    codeptr code;
    uintptr_t data;
};

void code_push(uintptr_t data, DECL_STATE);
void code_add(uintptr_t data, DECL_STATE);
void code_print(uintptr_t data, DECL_STATE);
void code_exit(uintptr_t data, DECL_STATE);

void code_subroutine(uintptr_t data, DECL_STATE);
void code_return(uintptr_t data, DECL_STATE);

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

uintptr_t stack_buf[16];

const struct instr *rstack_buf[16];

static inline void go(DECL_STATE) {
    struct instr ins = *ip;
    ins.code(ins.data, STATE);
}

void interpreter(void) {
    const struct instr *ip = &i_main;
    uintptr_t *sp = stack_buf;
    const struct instr **rsp = rstack_buf;
    go(STATE);
}

void code_push(uintptr_t data, DECL_STATE) {
    ip++;
    *(sp++) = data;
    go(STATE);
}

void code_add(uintptr_t data, DECL_STATE) {
    ip++;
    uintptr_t b = *(--sp);
    uintptr_t a = *(--sp);
    *(sp++) = a + b;
    go(STATE);
}

void code_print(uintptr_t data, DECL_STATE) {
    ip++;
    uintptr_t val = *(--sp);
    print(val);
    go(STATE);
}

void code_exit(uintptr_t data, DECL_STATE) {
    ip++;
    exit(0);
    go(STATE);
}

void code_subroutine(uintptr_t data, DECL_STATE) {
    const struct instr *sr = (const struct instr *) data;
    ip++;
    *(rsp++) = ip;
    ip = sr;
    go(STATE);
}

void code_return(uintptr_t data, DECL_STATE) {
    ip = *(--rsp);
    go(STATE);
}
