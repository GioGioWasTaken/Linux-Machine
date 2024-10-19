b *0x08048717
# set a break point where memset(replaced by gets) gets called.
# addr of p: 0x804a080
define hook-run
  x/1xw  &p 
  # our 1024 byte tile
end

define hook-continue
  x/1xw  &p 
end
