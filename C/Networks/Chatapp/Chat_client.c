#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
  int client_fd;
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr address;
  connect(client_fd, address.sa_data, size(address))

      return 0;
}
