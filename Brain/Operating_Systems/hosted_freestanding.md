# Hosted and free standing enviorenments
If you have done C or C++ programming in user-space, you have used a so-called Hosted Environment.
Hosted means that there is a C standard library and other useful runtime features.

Alternatively, there is the Freestanding version, which is what you are using here. Freestanding means that there is no C standard library, only what you provide yourself.

However, some header files are actually not part of the C standard library, but rather the compiler. These remain available even in freestanding C source code. In this case you use <stdbool.h> to get the bool datatype, <stddef.h> to get size_t and NULL, and <stdint.h> to get the intx_t and uintx_t datatypes which are invaluable for operating systems development, where you need to make sure that the variable is of an exact size (if you used a short instead of uint16_t and the size of short changed, your VGA driver here would break!). Additionally you can access the <float.h>, <iso646.h>, <limits.h>, and <stdarg.h> headers, as they are also freestanding. GCC actually ships a few more headers, but these are special purpose. 

## Headers that are implemented within the compiler:

`<stdbool.h>`
`<stddef.h>`
`<stdint.h>`
`<float.h>`
`<iso646.h>`
`<limits.h>`
`<stdarg.h>`
