# Threaded code demo

Some demonstrations of threaded code techniques

- `bytecode.c`: Bytecode (Not technically threaded)
- `direct.c`: Direct threaded code
- `indirect.c`: Indirect threaded code
- `pctc.c`: Primitive-centric threaded code
- `pctc_opt.c`: Primitive-centric threaded code (Optimized to encourage the compiler to use registers)

Primitive-centric threaded code is described in [Direct or Indirect Threaded?][gforth-pctc] in the Gforth manual.

[gforth-pctc]: https://gforth.org/manual/Direct-or-Indirect-Threaded_003f.html

Each of the demo files needs to be compiled along with / linked to `main.c` such as:

```console
$ gcc -o direct direct.c main.c
$ ./direct      # Run the demo
```

Or equivalently, using the convenience `Makefile`:

```console
$ make direct   # Build one demo
$ make          # Build everything
```

Each demo simply prints a number to show that it will run. The expected outputs are:

- `bytecode`: `2`
- `direct`: `2`
- `indirect`: `4`
- `pctc`: `6`
- `pctc_opt`: `6`
