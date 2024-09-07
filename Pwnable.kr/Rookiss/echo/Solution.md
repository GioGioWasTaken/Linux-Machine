### Misc info found so far
~~- we seem to be able to free cs:o by calling exit and answering n~~
~CS:O is referenced by echo1, which we can call afterwards.~
irrelvant to this.

# Primitives:
- name buffer
- buffer overflow primitive after echo is called
## Plan
- redirect control flow to my name primitive 
- use it as a ROP gadget

[!TIP] Just to have it on standby:
| Register | Argument|
|----------|----------|
| 1. `RDI`    | First argument|
| 2. `RSI`    | Second argument|
| 3. `RDX`    | Third argument |
| 4. `RCX`    | Fourth argument|
| 5. `R8`     | Fifth argument |
| 6. `R9`     | Sixth argument |
