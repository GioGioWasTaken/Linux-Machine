# Solution

- First of all there is a known bug with alloca. Look into that
- Perhaps also try to overflow int with a negative value.
# Approach:

- After some testing, we observe that whatever value i allocate, 22 more bytes  will be allocated so that esp is properly alligned.
- The stack must always be aligned, so we can't control the increment by the byte
- butttt we can control the increment by the stack alignment factor
- on this binary it happens to be 8 since it's a 32 bit binary
- so we have our exploit: move ESP upwards (deallocate data)
- and use our fgets to overwrite main's return address on the stack.
