#!/bin/bash
ROPgadget --binary libc-2.15.so | grep -F "$1" | awk '{print $1}' | xargs -I {} python is_ascii.py {}
