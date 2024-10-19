# Primitive

A 1024 long char array that we can manipulate with bf operations. These allow us to put and print values. It is "compiled" by means of iterating over that array and calling `do_brainfuck()` on its indexes, as checked by `strlen()`. 

# Looking into the binary

Immediately I saw that fgets reads 1024 bytes, not leaving space for the null terminator. I then looked for functions that manipulate strings, and there i found `strlen()` in the do_brainfuck() for loop. This means by switching the null terminator with another value, we can get an out of bounds read and write. But we only have 1024 characters, all of which are needed to move the pointer to that location. We can't use while loops. For now, this doesn't seem viable anymore.

Another thing of note, is that we can easily move the pointer outside the array by simply using < at the start. We can use  this to write /bin/sh at a known address, which is nice to have.

I started thinking what other things I could mofy that come in memory before the point `P` points to, and, Upon further checking:

`P` first points to the real addr of our "tape", located at `0x0804a0a0`
.plt.got table starts at `0x0804A000`

`
gdb-peda$ distance 0x0804a0a0 0x0804A000
From 0x804a0a0 to 0x804a000: -160 bytes, -40 dwords
`
also:
`
CANARY    : ENABLED
FORTIFY   : disabled
NX        : ENABLED
PIE       : disabled
RELRO     : Partial
`

the GOT, is therefore perfectly writable AND readable.

Then, a thought crossed my mind:

wait... What if we could overwrite p itself?! that would give us the ability to move the pointer anywhere we want!
`
gdb-peda$ x/1xw &p
0x804a080 <p>:  0x0804a0a0
gdb-peda$ distance 0x804a080 0x0804a0a0
From 0x804a080 to 0x804a0a0: 32 bytes, 8 dwords
` 
32 bytes? easy work.

After changing it, I understood that changing 1 byte of p would result in the attempt to change `P`'s next byte to fail. This of course happens because `P` now points to a new location and by calling `,` again, we are modifying that location. Perhaps there's a workaround but it doesn't come to mind at the moment, so I will tentatively take it as a constraint that we can only modify 1 byte of `P`.


This, if anything, can save us bytes on our way to the GOT table, so it's still a very valuable discovery.


# Exploit plan


1. We will read the address of "fgets" to find the libc base
2. We will replace fgets with system()
3. We will replace memset with gets()
4. Finally, we will replace getchar() with main(), calling the program again with the modified functions

pwned.
