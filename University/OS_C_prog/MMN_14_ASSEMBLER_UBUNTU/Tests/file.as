.entry MAIN
.entry LIST
MAIN: add r3, LIST
.extern fn1
.extern L3
jsr fn1 
LOOP: prn #48
lea STR, r6 
inc r6
mov *r6, L3
sub r1, r4 
cmp r3, #-6 
bne END
add r7, *r6
clr K
sub L3, L3
jmp LOOP 
END: stop 
STR: .string "abcd" 
LIST: .data 6, -9
.data -100 
K: .data 31 
