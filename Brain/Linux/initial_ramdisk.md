# General explaination
 In Linux systems, initrd (initial ramdisk) is a scheme for loading a temporary root file system into memory, to be used as part of the [Linux startup process].

initrd and initramfs (from initial ram file system) refer to two different methods of achieving this. Both are commonly used to make preparations before the real root file system can be mounted. 

Each scheme invovles setting up different parts of the file system in a different way, and they thus require build hooks that achieve different parts of this.

E.g.: 
- base: Includes essential files and binaries needed for the boot process, such as the basic shell and utilities.

- udev: Adds device management tools, which are necessary for detecting hardware during boot.

- autodetect: Detects and includes only the modules required for your system, reducing the size of the initramfs.

# Why?

The device drivers for this generic kernel image are included as loadable kernel modules because statically compiling many drivers into one kernel causes the kernel image to be much larger, perhaps too large to boot on computers with limited memory, or in some cases to cause boot-time crashes or other problems due to probing for nonexistent or conflicting hardware.

