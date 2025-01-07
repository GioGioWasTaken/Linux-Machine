# What are they?

They are similar in essence to file descriptors on linux, but can also point to processes, threads, windows, etc. Think of them as generic, system-wide, unique identifiers for different parts of programs in the windows operating system. 

Windows, unlike linux, ships with a window manager and all those things, so it can allow itself to manage it through its own implementation, which is why we would have handles for windows in the first place.
