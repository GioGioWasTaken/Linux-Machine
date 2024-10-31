#!/bin/bash
ROPgadget --binary libc-2.15.so --offset 5555e000 --badbytes "00-20|80-ff"| grep -F "$1" | awk '{print $1}'
