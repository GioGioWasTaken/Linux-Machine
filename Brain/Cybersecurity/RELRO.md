## RELRO:

## Full RELRO

Stands for `Relocation Read-Only`
Makes some areas in memory, most notably the `GOT table`, only readable and not writable.
setting the `LD_BIND_NOW` env var seems to have the same effect.

Using RELRO has a disadvantage. 
It makes the `GOT table` not writable, it has to resolve all the references immediately when the binary executes.
In large programs with thousands of symbols that need to be linked, this could cause a noticable delay in startup time. Therefore it's not a default compiler setting.



The normal process without RELRO is referred to as `lazy binding`.


**Mitigations:** 

Do not write to these areas, this would result in a segfault. Find a different area to target.


## Partial RELRO:

Partial RELRO is the default setting in GCC, and nearly all binaries you will see have at least partial RELRO.

From an attackers point-of-view, partial RELRO makes almost no difference, other than it forces the GOT to come before the BSS in memory, eliminating the risk of a buffer overflows on a global variable overwriting GOT entries.
