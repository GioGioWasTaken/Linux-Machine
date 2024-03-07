#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFFER 100

int main() {
  char message[BUFFER];

  int client_fd;
  client_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct addrinfo hints, *address_info;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;       // IPv4
  hints.ai_socktype = SOCK_STREAM; // Stream socket

  // Get address information for localhost and port 3440
  int status = getaddrinfo("localhost", "3440", &hints, &address_info);
  if (status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(EXIT_FAILURE);
  }

  // Try connecting to the first available address
  for (address_info = address_info; address_info != NULL;
       address_info = address_info->ai_next) {
    if (connect(client_fd, address_info->ai_addr, address_info->ai_addrlen) !=
        -1) {
      break; // Success, break the loop
    }
  }

  if (address_info == NULL) {
    perror("Connection failed");
    freeaddrinfo(address_info);
    exit(EXIT_FAILURE);
  }

  // while (strcmp(message, "Close")) {
  strcpy(message, "");
  printf("Type message to server: \n");
  fgets(message, BUFFER, stdin);
  send(client_fd, message, strlen(message), 0);
  //}

  freeaddrinfo(address_info);

  return 0;
}
