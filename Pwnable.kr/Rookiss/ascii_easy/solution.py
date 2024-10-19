from pwn import *
import sys
import time

context.arch="amd64"
context.kernel="amd64"
context.os="linux"


binary_name = "ascii_easy"
e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)

context.binary = e



def main():
    if(len(sys.argv) <2):
        print("Running locally")
        p = process(f"./{binary_name}")
    else:
        if(sys.argv[1] == "remote"):
            # or if using ssh:
            s = ssh(user='',host='pwnable.kr',port=2222,password='guest') 
            p= s.process(f"./{binary_name}") 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(f"./{binary_name}", gdbscript="b *", aslr=False)
        else:
            p = process(f"./{binary_name}")
    libc=e.libc
    pop_esi_edi =
    libc.address = 0x5555e000


main()
