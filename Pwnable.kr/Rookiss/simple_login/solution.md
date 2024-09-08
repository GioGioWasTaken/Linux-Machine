# Misc knowledge

- base64Decode:
    - this function stores the 64bit decoded version pointed to by `param1` in `param2`
    - `iVar1` determines the size of `param2`, and this is copied to `input`
    - conjecture:
        - by encoding a value in base 64, we can make that value get copied to input and then copied to the buffer inauth
        
- Auth:
 -  Auth has a memycpy overflow. We can overwrite EBP. ebp is moved to esp with leave. ret simply takes the value pointed to by ESP and jumps there. Normally that value would be EIP. But... Now the stack pointer points to an entirely different location. We just need to point ESP at a memory location that has the value 0x08049284(address of the win function)
