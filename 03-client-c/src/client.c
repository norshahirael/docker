#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

	int socket;
	struct sockaddr_in server;
	char message[1000];
	char server_reply[2000];

	//create socket
	socket = socket(AF_INET, SOCK_STREAM, 0);
	if (socket == -1){
		printf("Socket can't be created");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("172.18.0.3");
	server.sin_family = AF_INET;
	server.sin_port = htons (8998);

	//connect to remote server
	if (connect(socket, (struct sockaddr *)&server, sizeof(server))<0){
		puts("Connection failed");
		return 1;
	}
	puts("Connected");

	//server communication
	while (1){
		printf("Type your message: ");
		scanf("%s" , message);

		//send data
		if (send(socket, message, strlen(message), 0) <0){
			puts("Data fail to send");
			return 1;
		}
		//reply from server
		if (recv(socket, server_reply, 2000, 0) <0){
			puts("Fail to receive");
			break;
		}
		puts ("Message from server: ");
		puts (server_reply);
	}
	close (socket);
	return 0;
}
