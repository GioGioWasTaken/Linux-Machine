- - Debug using GDB-Peda
    - [Short Cheatsheet]()
- Use Ghidra
    - [Ghidra start](https://guyinatuxedo.github.io/02-intro_tooling/ghidra/index.html) 

- Possible reasons for segfaults:
	- In assembly, the OS expects some values, depending on their size, to be aligned in some specific manner. 4 byte values must end in a hex digit that's divisible by 4, and the same goes for 8 byte values such as ESP.
		- This can be beat by chaining a return addresses into the payload, before the target address, thus moving ESP to a location so that it's properly aligned and a segfault doesn't occur.



[Reverse engineering Resource list](https://gist.github.com/DtxdF/9c9297945bd7165c53b264ec597a9c39)
