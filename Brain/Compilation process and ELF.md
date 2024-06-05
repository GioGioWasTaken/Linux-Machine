There are 3 main stages to compilation. 

The first one is compiling source code to assembly (.s file extension).

The second stage is assembling `.s` files to .so (shared object) files. 

The third is the linking stage, where `.so` files and dynamically fetched library functions are all combined to one binary (depending on the type of linking, the used libraries might get attached to the binary file during compile time, or they might just be located during runtime)

TL;DR : `the linker` resolves references to undefined symbols.



When a file is executed, the OS runs `the loader` which:

1. allocates memory based on the program's needs as specified in the `text and data segments`
2. copies text and data segments to the `memory image`
3. copy env vars and program args into the stack
4. clear registers and set ESP in place
5. 

