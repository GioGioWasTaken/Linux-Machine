# Primitives

- We have vulnreable PAM module, and its source code. We need to find some way to log in with ssh such that we gain access to the flag.

# aptSSH

- this gives us the binaries. I seperated them using a python script, relying on the ELF magic bytes as a delimiter.

## SSHuser

- his password is retrieved from a file, and null terminated at the first occurance of a \n character.
- my guess is that if we log in as this user, we get the flag.
- A lot of anti-debugger countermeasures are taken. There might be a vulnrability in that logic, but I am currently looking elsewhere.
