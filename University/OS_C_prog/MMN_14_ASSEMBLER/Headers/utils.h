#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


void create_file(FILE *file);

void exit_current_file();

int isIllegalName(char * name);


int line_too_long_exists(char * file_name);

#endif

