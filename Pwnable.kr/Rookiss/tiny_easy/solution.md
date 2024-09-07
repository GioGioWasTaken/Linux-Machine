Consturct an env varible such that, the value we get, when treating the hex value of this env variable as a pointer, is the address of code we want to call.

Maybe a possible approach would be to store shellcode at an env var such that 
that shellcode is put into EAX
then, put the address of EAX into EDX. EDX will dereference the address stored in itself, and attempt to jump to the value stored at EAX, which wll be our instruction

observe that the difference between tiny_easy and the hacker's secret "tiny" or "tiny_hard" is not in the code, but in the fact that NX is enabled for tiny_easy.

from here we can be pretty sure that we want to inject shellcode into the env variables. The env variables are on the stack, and the stack is executable.




final approach:

1. hijack the first env variable, and overwrite it value so that it points to the stack addr of some env variable
2. overwrite the value of some_env_Variable to shellcode that spawns a shell.
as for step 2, let's try the following: 
```
export ALACRITTY_LOG=$(<payload)
```
