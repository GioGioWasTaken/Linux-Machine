import struct
arr= [0x3a746163	,0x73617020	,0x726f7773	,0x50203a64
,0x696d7265	,0x6f697373	,0x6564206e	,0x6465696e]
def little_endian(num):
    return struct.pack('<I', num).hex()
res =b""
for element in arr:
    res+=bytes.fromhex(little_endian(element))
print(res)
