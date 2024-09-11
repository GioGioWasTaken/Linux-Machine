# There are three types of buffering types

- The types can be switched to and fro using the `setvbuf` C standard library function. The types are as follows:
    * unbuffered: 
	+  When an output stream is unbuffered, information appears on the destination file or terminal as soon  as  written.
	+  `stderr` is always unbuffered.
	+  referred to as `_IONBF`.
    - line buffered:
	*  when it is line buffered, characters are saved up until a newline is output  or  input is  read  from  any stream attached to a terminal device (typically stdin).
	*  `referred to as _IOLBF`
    
    - `Default`: block buffered: 
	*  when  it  is  block buffered(default),  many  characters are saved up and written as a block

    -  the function can also take a parameter fully buffered, `referred to as _IOFBF`
- The function `fflush` may be used to force  the  block  out  early.
