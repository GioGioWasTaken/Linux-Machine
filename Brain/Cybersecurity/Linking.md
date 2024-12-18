## Lazy binding process:
Whenever an external symbol is called, the assembly will call a stub, which is a block of assembly code that either invokes the dynamic linker to locate and write the address of the symbol into the GOT, or if the address exists jumps there.


# ld.so and linux-ld.so

This is where the magic happens. These binaries are responsible for linking all the `.so` files we use when programming with `C`. They locate the symbols used by the dynamically linked program, and they resolve these entries inside the `.got` table [read_more](GOT_PLT.md).


`ld.so` is used for the older `a.out` file format, and `linux-ld.so` is used for the far more modern [ ELF ](ELF.md) format. 

They search for the `.so`s like so (from `man ld.so`):

### First things first:
   The dynamic linker can be run either indirectly by running some dynamically linked program or shared object (in which case no command-line options to the dynamic linker can be passed and, in the `ELF` case, the dynamic linker which is stored in the `.interp` section of the program is executed)

   or directly by running: `/lib/ld-linux.so.*  [OPTIONS] [PROGRAM [ARG]`


### Locating the shared objects:

When resolving shared object dependencies, the dynamic linker first inspects each dependency string to see if it contains a slash (this can occur if a shared object pathname containing slashes was specified at link time).  If a slash is found, then the dependency string is interpreted as a (relative or absolute) pathname, and the shared object is loaded using that pathname.

Otherwise, If a shared object dependency does not contain a slash, then it is searched for in the following order:

(1)  Using the directories specified in the `DT_RPATH` dynamic
    section attribute of the binary if present and `DT_RUNPATH`
    attribute does not exist.

(2)  Using the environment variable `LD_LIBRARY_PATH`, unless the
    executable is being run in secure-execution mode (see
    below), in which case this variable is ignored.

(3)  Using the directories specified in the `DT_RUNPATH` dynamic
    section attribute of the binary if present.  Such
    directories are searched only to find those objects required
    by `DT_NEEDED` (direct dependencies) entries and do not apply
    to those objects' children, which must themselves have their
    own `DT_RUNPATH` entries.  This is unlike `DT_RPATH`, which is
    applied to searches for all children in the dependency tree.

(4)  From the cache file `/etc/ld.so.cache`, which contains a
    compiled list of candidate shared objects previously found
    in the augmented library path.  If, however, the binary was
    linked with the `-z nodefaultlib` linker option, shared
    objects in the default paths are skipped.  Shared objects
    installed in hardware capability directories (see below) are
    preferred to other shared objects.

(5)  In the default path `/lib`, and then `/usr/lib`.  (On some
    64-bit architectures, the default paths for 64-bit shared
    objects are `/lib64`, and then `/usr/lib64`.)  If the binary was
    linked with the `-z nodefaultlib` linker option, this step is
    skipped.


It is thanks to the metadata stored in the `ELF` binary, that it's able to identify which are the dependencies it needs to resolve by looking into these directories. 


The elf also contains a `.gnu.hash`  section, which will serve it to efficiently retrieve the function in question, for example `puts`, from `libc.so.6`'s symbol table.
