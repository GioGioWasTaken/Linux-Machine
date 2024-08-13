#ifndef UTILS_H
#define UTILS_H

#include "first_pass.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void create_file(FILE *file);

void exit_current_file();

int isIllegalName(char * name);

void print_assembler_warning(int error_code, code_location am_file);

void print_assemble_time_error(int error_code, code_location am_file);

int line_too_long_exists(char * file_name);

void skipWhitespace(char** str);


void removeTrailingNewline(char *str);

#endif

