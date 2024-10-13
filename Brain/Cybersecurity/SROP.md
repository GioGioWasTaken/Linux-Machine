# Sigreturn-oriented programming

When a program is running and a signal occurs, the kernel pauses the process execution in order to jump to a signal handler routine. An example of this could be a user keyboard interrupt which triggers a SigKill.

So that execution may be resumed safely after the handler completes, the context of that process is pushed onto the stack. When the handler is finished, a sigreturn() is called which will restore the context of the process by popping the values from the stack.


[this](https://www.youtube.com/watch?vd0gS5TXarXc) youtube video explains signals.


# Trigger conditions

We need to use some gadgets in order to trigger the signal. Essentially we need to make a syscall whilst the rt_sigreturn syscall number is in the rax register.

## x64

mov rax, 0x0f; syscall; ret

## x86
mov eax, 0x77; int 0x80; ret
