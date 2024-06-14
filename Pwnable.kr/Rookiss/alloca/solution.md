# Solution

- First of all there is a known bug with alloca. Look into that
- Perhaps also try to overflow int with a negative value.
# Approach:

- allocate a very large positive number (just allocate a negative number and calculate with twos complement) such that the +4 added from the canary will make it look right back.
- now the size of the buffer is really small, and the size of bytes you can allocate is huge.
- wreak havoc :)
