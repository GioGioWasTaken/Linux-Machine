#!/bin/bash
ROPgadget --binary ascii | grep -F "$1" | awk '{print $1}' | xargs -I {} python is_ascii.py {}
