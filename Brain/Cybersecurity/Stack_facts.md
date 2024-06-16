# Stack alignment
Alignment Requirement: Many systems require that memory allocations be aligned to certain boundaries (e.g., 16 bytes). Proper alignment can improve performance due to the way CPUs handle memory access, and certain types of data may have specific alignment requirements.

# How does this look in assembly?

Well, it can be as simple as:

```asm

sub     rsp, 15        ; Add padding
and     rsp, 0xFFFFFFFFFFFFFFF0 ; Align to 16 bytes
```
or, in 32 bit:
```asm

sub     esp, 15        ; Add padding
and     esp, 0xFFFFFFF0 ; Align to 16 bytes
```

... And it can also look like this:

```asm
lea    rdx, [rax+8]         ; Add 8 for alignment adjustment
mov    eax, 16              ; Set divisor to 16
sub    rax, 1               ; Subtract 1 for rounding up
add    rax, rdx             ; Add the current size plus 8 plus 15
mov    ecx, 16              ; Set divisor to 16
mov    edx, 0               ; Clear edx for division
div    rcx                  ; Divide rax by 16
imul   rax, rax, 16         ; Multiply quotient by 16
```
