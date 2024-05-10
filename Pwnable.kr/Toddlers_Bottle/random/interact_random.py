from pwn import *

user ='random'
host = 'pwnable.kr'
password = 'guest'
port=2222

machine = ssh(user=user, host=host, password=password, port=port)

proc = machine.process("/home/random/random")
proc.sendline("3039230856")
print (proc.recvall())
