- A floppy disk isn't volatile. As such, it is catagorized as a `persistent storage device`. The maximum size of data that can be stored a floppy disk is 1.4MB.
- When reading from a floppy disk, the smallest unit that can be read is a `sector`, a group of 512 contiguous bytes.
- a group of 18 `sectors` is caled a `track`.
- each side of a `floppy disk` has 80 tracks. So: 80 * 18 *512B=1.4MB
- A `floppy drive` is an interface to I/O operations on a `floppy disk`.
 ![[Pasted image 20240630114454.png]]
 - The drive has 2 `heads`  
 - We can map sectors of disk into `RAM` using BIOS services.


