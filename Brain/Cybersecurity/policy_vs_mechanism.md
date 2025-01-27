# Intro:
The distinction between mechanism and policy is one of the best ideas behind the
Unix design. Most programming problems can indeed be split into two parts: “what
capabilities are to be provided” (the mechanism) and “how those capabilities can be
used” (the policy). If the two issues are addressed by different parts of the program,
or even by different programs altogether, the software package is much easier to
develop and to adapt to particular needs.

## For example: 

Where drivers are concerned, the same separation of mechanism and policy applies. The floppy driver is policy free—its role is only to show the diskette as a continuous array of data blocks. Higher levels of the system provide policies, such as who may access the floppy drive, whether the drive is accessed directly or via a filesystem, and whether users may mount filesystems on the drive. Since different environments usu- ally need to use hardware in different ways, it’s important to be as policy free as possible.
