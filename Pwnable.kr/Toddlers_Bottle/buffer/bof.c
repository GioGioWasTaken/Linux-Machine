#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void func(int key) {
  char overflowme[32];
  printf("overflow me : ");
  gets(overflowme); // smash me!
  if (key == 0xcafebabe) {
    system("/bin/sh");
  } else {
    printf("Nah..\n");
  }
}
int main(int argc, char *argv[]) {
  func(0xdeadbeef);
  return 0;
}

// we need to jump the point after jne, to get system result
// func+49 -> 0x5655565d
// ret of func is located at 0x5655568a
