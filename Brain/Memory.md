- When you hear the term word, know that it refers to the size of registers on the system in question. Thus, in 32 bit a `word` is 4 bytes, and in 64 bit, a `word` is 8 bytes. Of course, `double-word` and `quad-word` follow the same pattern.
- The theoretical limit of 32 bit, and 64 bit architectures is respectively, 2^32 and 2^64 bytes of memory.  (4GB for 32 bit.)


- "Another neat fact is libc.so and ld.so are consistently spaced in memory. They'll be at consistent offsets from each other! This is a byproduct of something known as mmap relativity, where pages allocated by mmap are usually adjacent, and if not, always at a relative offset. This will be useful later."
- [[Virtual memory]]
- [[RAM]] 
