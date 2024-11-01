# Things I discovered while pwnin' !

- Argv and envp can be fully controlled with pwntools.
- argv[0] (specifically) can be controlled with a symlink, by linking a program with a name of our choice to the target binary, and then running this program.
- We can pass no input to scanf by passing - to a %d modifier.
- We can use ln -s /bin/sh "something" in order to make "something" be a symbolic link to /bin/sh. This will cause execve("something") to be equivalent to execve("/bin/sh"), which is useful when replacing the GOT address of say, a puts() function with system.
- `fmtstr_payload(offset(usually 6),{ <absolute addr> :<value> },write_size='int')`
- ///////....bin/sh is a valid way to call it. This is true for any path in general.



# Useful terminal commands

readelf -l {elf}  - find useful information like the entry point of the binary, architecture, sections, etc

objdump -j .plt -d {elf} - print plt function addresses
