#!/bin/bash
gcc spacebarServer.c -o spacebarServer -lX11 -lXtst
./spacebarServer
