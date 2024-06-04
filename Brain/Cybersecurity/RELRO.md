## RELRO:

Makes some areas in memory, most notably the GOT table, only readable and not writable.

**Mitigations:** 

Do not write to these areas, this would result in a segfault. Find a different area to target.
