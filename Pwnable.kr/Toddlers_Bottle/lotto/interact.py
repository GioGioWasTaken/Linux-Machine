import pexpect
import sys
# 1. Run ./lotto
child = pexpect.spawn('./lotto')

# 2. Wait for the initial menu
child.expect("- Select Menu -")

# 3. Send "1" to play lotto
child.sendline("1")
print("Connected. Cracking....")

# 4. Send a large input
child.sendline("A" * 200000)

# 5. Log process output to console
print (child.read())
# Wait for the process to finish
child.expect(pexpect.EOF)
