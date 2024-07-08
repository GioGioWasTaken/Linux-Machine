#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
int main()

{

static char *s[] = {"zy", "xw", "vut", "srq", "ponmlkjih", "gfed", "cba"};
printf("%c", s[6][0]);

printf("%c", *(s[2]+2));

printf("%c", (*s[6])+2);

printf("%c", 'p' + **s - 'w');

puts(s[2]+2);
}
