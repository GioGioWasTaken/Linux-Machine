#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len;
  char buffer[BUFFER_SIZE];

  // Create the server socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Set up the server address and port
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  // Bind the server socket
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 10) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on http://localhost:%d\n", PORT);

  while (1) {
    // Accept a client connection
    client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }

    // Read the HTTP request sent by the client
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
      perror("read failed");
      exit(EXIT_FAILURE);
    }

    printf("HTTP request sent by client: %s", buffer);

    // Send the HTML response with the input box
    char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                      "<html><body>"
                      "Hi, I was bored so I made an http server.\n";
    write(client_fd, response, strlen(response));

    // Close the client connection
    close(client_fd);
  }

  // Close the server socket
  close(server_fd);

  return 0;
}
