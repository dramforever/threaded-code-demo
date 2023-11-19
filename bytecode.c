#include <stdint.h>
#include <stdlib.h>

#include "base.h"

#define OP_EXIT 0
#define OP_PUSH 1
#define OP_ADD 2
#define OP_PRINT 3

const uint8_t program[] = {
    OP_PUSH, 1, OP_PUSH, 1, OP_ADD, OP_PRINT, OP_EXIT,
};

const uint8_t *ip = program;

uintptr_t stack_buf[STACK_SIZE];
uintptr_t *sp = stack_buf;

void interpreter(void) {
    for (;;) {
        switch (*ip) {
        case OP_EXIT:
            ip++;
            exit(0);
            break;

        case OP_PUSH:
            ip++;
            uintptr_t operand = *(ip++);
            *(sp++) = operand;
            break;

        case OP_ADD:
            ip++;
            uintptr_t b = *(--sp);
            uintptr_t a = *(--sp);
            *(sp++) = a + b;
            break;

        case OP_PRINT:
            ip++;
            uintptr_t val = *(--sp);
            print(val);
            break;
        }
    }
}
