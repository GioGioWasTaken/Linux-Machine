#! /usr/bin/python3
import sys
import pexpect
target = "nc pwnable.kr 9009"
p = pexpect.spawn(target)
p.interact()

# I wanted to automate this, but lowkey not worth it. Do it by hand.
# just set a negative number. -1000000 <500 && - (-1000000) = +1000000
