b *0x08048742
r
# this will go to the code the compiler generated for alloca
b *0x08048838
# break before ret


#  b *0x80487e9 to stop before fgets, see where it reads input from and where it writes it to, so we can adjust buffer. this has value because this is where we can write our data to, so if we can find a way to overflow the location we write to, or the amount allowed for us to write...
