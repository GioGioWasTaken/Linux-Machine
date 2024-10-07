

# Primitives

- We can leak a value by specfying (+|-|*...) followed by a number.

# Canary leak 
|       |   0x080493be      8b45f4         mov eax, dword [var_ch]
|       |   0x080493c1      6533051400..   xor eax, dword gs:[0x14]


canary is located at $EBP -0xc


1428 byte offset from the location of the struct ($EBP-0x510).
