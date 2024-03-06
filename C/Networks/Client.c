#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define URL_len 100

int main() {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    printf("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  char URL[URL_len];
  printf("Please enter the site URL here:\n");
  if (fgets(URL, sizeof(URL), stdin) == NULL) {
    fprintf(stderr, "Error reading input.\n");
    exit(EXIT_FAILURE);
  } else {
    printf("URL chosen: %s", URL);
  }
  struct addrinfo hints, *result, *rp;
  int status;
  memset(&hints, 0, sizeof(hints));
  if (status != 0) {
    fprintf(stderr, "Failure when looking up address: %s \n",
            gai_strerror(status));
  }

  struct sockaddr_in sa;
  //  inet_pton(AF_UNSPEC, *ip, &(sa.sin_addr));

  // Close the socket when done
  close(socket_fd);

  return 0;
}
