// general use headers
#include <stdio.h>
#include <string.h>
// network headers
#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
// keyboard signal
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <X11/extensions/XTest.h>

#define PORT 9000
#define Pause "Pause" 
#define Close "Close"

void printHex(char * str){
	for(int i = 0; i<strlen(str);i++){
		printf("%02x",(unsigned char) str[i]);
	}
	puts("\n");
}

void send_key(Display *display, KeySym keysym) {
    KeyCode keycode = XKeysymToKeycode(display, keysym);
    XTestFakeKeyEvent(display, keycode, True, CurrentTime);
    XFlush(display);
    usleep(400); // Adjust delay as necessary
    XTestFakeKeyEvent(display, keycode, False, CurrentTime);
    XFlush(display);
}


int main(){
	//initialize display
	Display *display;
	display = XOpenDisplay(NULL);


	// intialize sockets as needed
	struct sockaddr_in server_addr;
	char Request[sizeof(Pause)+1];
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
	 /* Prevent bind errors caused by OS not freeing up resources yet. */
	int optval = 1;
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0){
		perror("Failed to set socket option");
		exit(EXIT_FAILURE);
	}
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
	printf("Server listening on port %d.\nWaiting for client to send its desired signal.\n", PORT);
	int clientfd = accept(server_fd, 0, 0);
	if(clientfd < 0){
		perror("Error accepting incoming client connection");
		exit(EXIT_FAILURE);
	}
	printf("Client accepted\n");
	fflush(stdout);
	fd_set readfds;
	// Clear the set
	FD_ZERO(&readfds);
	FD_SET(clientfd, &readfds);
	// Add the socket file descriptor to the set
	// this would have been very useufl if we had multiple clients, just a cool thing I learned.
	struct timeval timeout;
	timeout.tv_sec= 7200; // 2 hours in seconds
	// Wait until there's data to read from the socket
	int activity = select(clientfd + 1, &readfds, NULL, NULL, &timeout);
	while(1){
		if (activity < 0) {
			perror("ERROR in select");
			exit(1);
		} else if (activity == 0) {
			printf("Timeout occurred.\n");
			exit(0);
	} else {
			// Data is ready to be read
			memset(Request, 0, sizeof(Request));
			int n = read(clientfd, Request, sizeof(Request)-1);
			if (n < 0) {
				perror("ERROR reading from socket");
				exit(1);
			}
			printf("Request recieved from client: %s\n", Request);
			if(strncmp(Request, Pause,5) == 0){
				// Send spacebar signal.
				puts("Sending spacebar (pause) signal.");
				/* Compiler will optimize printf to puts anyways, but i'm cool so I don't printf constant string values.*/
				
				send_key(display, XK_space);
				sleep(1);
				continue;
			}
			if(strncmp(Request, Close, 5) == 0){ // constant value, no need for strncmp
				puts("Closing server.\n");
				break;
			}
			else{
				puts("Request in hex:\n"); /* debugging purposes */
				printHex(Request);
				puts("Invalid request. Continuing to listen.\n");
				continue;
			}
		}

	}
	close(clientfd);
	close(server_fd);

	return EXIT_SUCCESS;

}


