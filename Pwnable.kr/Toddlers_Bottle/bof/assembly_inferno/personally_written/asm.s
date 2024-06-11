.global _start
.intel_syntax noprefix

_start:
  mov rax, 1
  mov rdi, 1
  lea rsi, [schizo]
  mov rdx, 101 
  syscall

  mov rax, 60
  mov rdi, 69
  syscall

schizo:
  .asciz "BORN TO WRITE WORLD IS A CHUNK 鬼神 LSB Em All 1972 I am THE mov man 410,757,864,530 CORRUPTED POINTERS"
