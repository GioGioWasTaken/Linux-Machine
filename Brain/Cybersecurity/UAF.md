# UAF

a UAF or Use-After-Free exploit involves a case where we can free a pointer and then call it again later.

If a pointer is free()'d, the next malloc is likely to allocate at the same location. If the pointer is used again, it will misread the state of the heap, because it has our new data. This can lead to all sorts of mischief.

## Heap behaviour and chunks
