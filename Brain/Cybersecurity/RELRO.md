## RELRO:

Stands for `Relocation Read-Only`
Makes some areas in memory, most notably the `GOT table`, only readable and not writable.
setting the `LD_BIND_NOW` env var seems to have the same effect.  Using RELRO has a disadvantage (not at all an issue in modern hardware), Since it makes the `GOT table` not writable, it has to resolve all the references immediately when the binary executes.

The normal process without RELRO is referred to as `lazy binding`.


**Mitigations:** 

Do not write to these areas, this would result in a segfault. Find a different area to target.
