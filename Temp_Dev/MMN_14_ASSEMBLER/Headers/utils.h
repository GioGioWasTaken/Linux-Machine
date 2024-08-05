#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
FILE * create_file(const char *filename);

void exit_current_file();
#endif

