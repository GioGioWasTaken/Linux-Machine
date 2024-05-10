#include <stdlib.h>
int main() {
  system("$(printf)");
  system("echo $(<$(printf %s%s fl ag))");
  return 0;
}
