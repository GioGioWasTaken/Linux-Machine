b *0x8048603 
# break at format string loop, when read syscall is called
r
b *0x8048615
# break at printf
b *0x08048791
# break at return address of fsb
find 0x0804a060
