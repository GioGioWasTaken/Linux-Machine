b *0x08048555 
# first malloc
b *0x08048565
# second malloc
b *0x08048575
# third malloc
b *main+181 
# ni is puts
b * 0x08048602
# before function epilogue, after unlink
