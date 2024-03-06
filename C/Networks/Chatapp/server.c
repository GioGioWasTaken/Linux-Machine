#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFER 1000;
int main() {
  int server_fd;
  struct addrinfo hints, *res;
  // essentially sockaddr is just the address we are binding the socket to.
  // We are adding the details of the address. in this case
  memset(&hints, 0, sizeof hints); // get rid of garbage values, structs are
                                   // contiguous, essentially arrays.
  hints.ai_family = AF_UNSPEC;     // use IPv4 or IPv6, whichever
  hints.ai_socktype = SOCK_STREAM; // stream socket
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
  int addr = getaddrinfo(NULL, "3490", &hints, &res); // local host, port 3490,
  if ((server_fd =
           socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  bind(server_fd, res->ai_addr, res->ai_addrlen);
  int backlog = 5; // Maximum length of the queue of pending connections
  listen(server_fd, backlog);

  char message[50];
  fgets(message, BUFFER, );

  printf("Client says: %s\n", message);

  return 0;
}
