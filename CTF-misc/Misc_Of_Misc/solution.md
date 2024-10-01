

- Use ROP to redirect code execution to another gets call.
- This time gets will be called on an executable address.
- We will utilise custom shellcode that movs /bin/sh from a known location in the DATA section (fixed addresses) 
