

- Argv and envp can be fully controlled with pwntools.
- argv[0] can be controlled with a symlink, by linking a program with a name of our choice to the target binary, and then running this program.
- We can pass no input to scanf by passing - to a %d modifier.
- We can use ln -s /bin/sh "something" in order to make "something" be a symbolic link to /bin/sh. This will cause execve("something") to be equivalent to execve("/bin/sh"), which is useful when replacing the GOT address of say, a puts() function with system.



# Useful terminal commands

readelf -l {elf}  - find useful information like the entry point of the binary, architecture, sections, etc

objdump -j .plt -d {elf} - print plt function addresses
