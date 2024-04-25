#include <stdio.h>
#include <string.h>
unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char *p) {
  printf("Pointer points to: %c\n", *p);
  int *ip = (int *)p;
  int i;
  int res = 0;
  for (i = 0; i < 5; i++) {
    res += ip[i];
  }
  return res;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage : %s [passcode]\n", argv[0]);
    return 0;
  }
  if (strlen(argv[1]) != 20) {
    printf("passcode length should be 20 bytes\n");
    printf("Length of current passcode is: %lu", strlen(argv[1]));
    return 0;
  }

  if (hashcode == check_password(argv[1])) {
    printf("Flag Found!!!! Now use this input inside the challenge.");
    return 0;
  } else
    printf("%lu\n", check_password(argv[1]));
  printf("wrong passcode.\n");
  return 0;
}
