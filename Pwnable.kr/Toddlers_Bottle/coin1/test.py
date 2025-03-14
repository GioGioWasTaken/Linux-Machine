from pwn import *

def play():
    p = remote("pwnable.kr", 9007)
    print(p.recvuntil(" 3 sec... -\n") )
    print(p.recvline())
    l = 0
    r = int(p.recvuntil(" C").decode()[3:-2])-1
    p.recvline()
    print(f"Coin amount: '{r}'")
    while l < r:
        m = (l + r) // 2
        weight = getWeight(l, m, p)
        
        if weight % 10 != 0:
            r = m
        else:
            l = m + 1
    print("Coin index found. Sending it to server...")
    p.sendline(str(r+1))
def sendWeight(start, end):
    output = ""
    for i in range(start, end + 1):  # inclusive
        output += str(i) + " "
    output= output.strip()
    print(f"-------------------------\nsending coin index range:\n{output}\n ----------------------------\n")
    return output
def getWeight(start, end, process):
    process.sendline(sendWeight(start,end))
    weight = int(process.recvline().decode()[:-1])
    print(f"Weight for given range is: {weight}")
    return weight
if __name__ == "__main__":
    play()
