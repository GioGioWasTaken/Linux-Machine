# The primitive is GOD
- Rememeber your primitives. All of them.
-  If you have a primitive, don't get lost in the other details of the binary file.

# Delve deep into the mechanisms of the assembly
- Always look for the exact meaning of the assembly. ret doesn't "return the `EIP` address" it returns where it THINKS the `EIP` address is(ret = jmp [ESP]). Meaning, an `EBP` overwrite is an `EIP` overwrite.
- "I could solve this if I had X" - check if you can make X with your current primitives.

# "I have no idea what this even does... How do I approach this"

- Worse thing you can do is freeze. Think of very very simple inputs, that produce likely unintended results. Slowly understand what's happening. Rely on discompiled code. Rely on LLMs, rely on everything. Your goal is to understand what the hell this awful piece of code does, and then break it.


# "This doesn't make any sense"

- Go slow. Check *everything*.
  * Sometimes, the decompiled code will have mistakes that make it unintelligible, and they sometimes won't be obvious. Go to the assembly.
      + For example, a for loop identified as a while loop.
      + sometimes, you renamed a variable the wrong way and you're misleading yourself
  * Make sure you trace everything to its root.
