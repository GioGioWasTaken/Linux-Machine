#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 3440
#define BUFFER_SIZE 100
int main() {
  int server_fd;
  char msg[BUFFER_SIZE];
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address = {AF_INET, htons(PORT), 0};
  // IPv4, convert port to network byte order, localhost ip.
  bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  // the socket fd is now bound to the localhost address on PORT.
  int backlog = 5; // Maximum length of the queue of pending connections
  listen(server_fd, backlog);
  while (msg != "Close") {
    int client_fd = accept(server_fd, 0, 0);
    int bytes_recieved = recv(client_fd, msg, BUFFER_SIZE, 0);
    msg[bytes_recieved] = '\0';
    printf("Received data from client: %s\n", msg);
    close(client_fd);
  }

  close(server_fd);
  return 0;
}
