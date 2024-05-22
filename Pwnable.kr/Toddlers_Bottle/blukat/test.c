#include <stdio.h>
#include <string.h>
char *key =
    "3\rG[S/"
    "%\x1c\x1d#0?\rIS\x0f\x1c\x1d\x18;,4\x1b\x00\x1bp;5\x0b\x1b\x08\x45+";
char flag[100];
void calc_flag(char *s) {
  int i;
  for (i = 0; i < strlen(s); i++) {
    flag[i] = s[i] ^ key[i];
  }
  printf("%b\n", flag);
  printf("%x\n", flag);
  printf("%s\n", flag);
}
int main() {
  char *s = "a";
  calc_flag(s);
  return 0;
}
