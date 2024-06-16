#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT 9000
#define Password "Pause" //  obviously don't do this if you are dealing with anything that has actual significence. This is just running on my home network, though.

// #include <windows.h> // this file does not exist on linux hosts, uncomment when moving over to docker windows container.
int main(){
	struct sockaddr_in server_addr;
	char password[sizeof(Password)];
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0 ){
		perror("Error creating server socket.");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr)); // clear garbage values
	/* setting basic server configuration */
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

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
	printf("Server listening on port %d.\nWaiting for client to send its desired signal.", PORT);


}


