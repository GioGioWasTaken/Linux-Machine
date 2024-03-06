#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define BUFFER 100
int main() {
  char message[BUFFER];

  int client_fd;
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr address = {AF_INET, htons(3440), 0};
  // as programmed in server.c, the server is localhost, IPv4.
  if (connect(client_fd, (struct sockaddr *)&address, sizeof(address) == -1)) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }
  while (strcmp(message, "Close")) {
    send(client_fd, message, strlen(message), 0);
    printf("Type message to server: \n");
    fgets(message, BUFFER, stdin);
  }
  return 0;
}
