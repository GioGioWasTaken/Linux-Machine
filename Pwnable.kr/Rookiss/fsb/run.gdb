b *0x8048603 
# break at format string loop, when read syscall is called
r
b *0x8048615
# just so we can skip after printf
find 0x0804a060
