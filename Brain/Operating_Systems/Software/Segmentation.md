# Segmentation
#### syntax example:
- 0000:7c00h is used in assembly language programming, particularly with x86 architecture, to represent a segmented memory address.
- 0000 is the segment address.
- 7c00h (or 0x7c00 in more common hexadecimal notation) is the offset within that segment.

#### In real-mode addressing, the physical address is calculated as:
Physical Address=(Segment×16)+OffsetPhysical Address=(Segment×16)+Offset

So, for 0000:7c00h, the physical address would be:

Physical Address=(0000×16)+7c00 -> 7c00


- This address has special meaning, it's the address where the first bootsector is located.
