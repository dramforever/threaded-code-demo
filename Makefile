.POSIX:
.SUFFIXES:

# No default rules
MAKEFLAGS = -r

CC = gcc
CFLAGS = -O3 -Wall -Wextra -Wno-unused-parameter

DEMOS = bytecode direct indirect pctc pctc_opt

all: $(DEMOS)

clean:
	rm -f $(DEMOS)

%: %.c main.c base.h
	$(CC) $(CFLAGS) -o $@ $< main.c
