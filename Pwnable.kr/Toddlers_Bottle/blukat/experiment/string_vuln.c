#include <stdio.h>
#include <string.h>
int main() {
  char password[100];
  FILE *fp = fopen("password", "r");
  fgets(password, 100, fp);
  char buf[100];
  printf("guess the password!\n");
  fgets(buf, 128, stdin);
  if (!strcmp(password, buf)) {
    printf("Nice");
  } else {
    printf("wrong guess!\n");
  }
  return 0;
}
