## ABI - Application Binary Interface
The ABI of a system defines how library function calls and kernel system calls are actually done. This includes whether parameters are passed on the stack or in registers, how function entry points are located in libraries, and other such concerns.

When using static linkage, the resulting executable depends on the kernel using the same ABI as the one the executable was built for; when using dynamic linkage, the executable depends on the libraries' ABI staying the same.
