# address where ret in shell is executed.
x/12i 0x804a02c
b *shellcode
r
x/12i 0x804a02c
# put breakpoint at shellcode execution
b *0xffffd4cc
c
