# Finding one gadgets

If one_gadget and Angry_gadget both fail to find one_gadgets, we can look for them manually. Here's an example of how:

```bash
virtual@mecha:~$ ldd buf64 | grep libc
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ffff77f3000)
virtual@mecha:~$ strings -tx /lib/x86_64-linux-gnu/libc.so.6 | grep /bin/sh
1a3f20 /bin/sh
virtual@mecha:~$ objdump -M intel -d /lib/x86_64-linux-gnu/libc.so.6 | grep execve -B5 | grep rdi -C3 | grep 1a3f20 -C3
--
   d975a: 49 8d 7d 10           lea    rdi,[r13+0x10]
   d975e: e8 4d 6f f4 ff        call   206b0 <*ABS*+0x953c0@plt>
   d9763: 48 8d 3d b6 a7 0c 00  lea    rdi,[rip+0xca7b6]        # 1a3f20 <_libc_intl_domainname@@GLIBC_2.2.5+0x186>
   d976a: 48 89 da              mov    rdx,rbx
   d976d: 4c 89 ee              mov    rsi,r13
   d9770: e8 8b f8 ff ff        call   d9000 <execve@@GLIBC_2.2.5>
--
   d9a2c: e8 7f 6c f4 ff        call   206b0 <*ABS*+0x953c0@plt>
   d9a31: 48 8b 8d 60 ff ff ff  mov    rcx,QWORD PTR [rbp-0xa0]
   d9a38: 48 8b 55 90           mov    rdx,QWORD PTR [rbp-0x70]
   ==>d9a3c: 48 8d 3d dd a4 0c 00  lea    rdi,[rip+0xca4dd]        # 1a3f20 <_libc_intl_domainname@@GLIBC_2.2.5+0x186>
   d9a43: 48 89 ce              mov    rsi,rcx
   d9a46: e8 b5 f5 ff ff        call   d9000 <execve@@GLIBC_2.2.5>
--
   fccd9: e8 52 7b 00 00        call   104830 <__close@@GLIBC_2.2.5>
   ==>fccde: 48 8b 05 c3 d1 2d 00  mov    rax,QWORD PTR [rip+0x2dd1c3]        # 3d9ea8 <__environ@@GLIBC_2.2.5-0x31b0>
   fcce5: 48 8d 74 24 40        lea    rsi,[rsp+0x40]
   fccea: 48 8d 3d 2f 72 0a 00  lea    rdi,[rip+0xa722f]        # 1a3f20 <_libc_intl_domainname@@GLIBC_2.2.5+0x186>
   fccf1: 48 8b 10              mov    rdx,QWORD PTR [rax]
   fccf4: e8 07 c3 fd ff        call   d9000 <execve@@GLIBC_2.2.5>
--
   fdb89: e8 a2 6c 00 00        call   104830 <__close@@GLIBC_2.2.5>
   ==>fdb8e: 48 8b 05 13 c3 2d 00  mov    rax,QWORD PTR [rip+0x2dc313]        # 3d9ea8 <__environ@@GLIBC_2.2.5-0x31b0>
   fdb95: 48 8d 74 24 70        lea    rsi,[rsp+0x70]
   fdb9a: 48 8d 3d 7f 63 0a 00  lea    rdi,[rip+0xa637f]        # 1a3f20 <_libc_intl_domainname@@GLIBC_2.2.5+0x186>
   fdba1: 48 8b 10              mov    rdx,QWORD PTR [rax]
   fdba4: e8 57 b4 fd ff        call   d9000 <execve@@GLIBC_2.2.5>
```



What did he do here?
    1. Found offset of `/bin/sh` string.
    2. Disassembled libc and found all `execve` calls and printed 5 instructions before it.
    3. Piped that output and found `rdi` string and 3 instructions before and after it.
    4. Piped that output and found refrences of `/bin/sh` string location.
