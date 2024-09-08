

- Rememeber your primitives. All of them.
-  If you have a primitive, don't get lost in the other details of the binary file.


- Always look for the exact meaning of the assembly. ret doesn't "return the `EIP` address" it returns where it THINKS the `EIP` address is(ret = jmp [ESP]). Meaning, an `EBP` overwrite is an `EIP` overwrite.
