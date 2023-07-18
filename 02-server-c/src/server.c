#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
	
	int socketfd, client_sock, c, read_size;
	struct sockaddr_in servers, client;
	char client_message[2000];

	//sockeet creation
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1){
		printf("Socket created failed");}
	puts("Socket created successfull");

	//prepare socket address
	servers.sin_family = AF_INET;
	servers.sin_addr.s_addr = INADDR_ANY;
	servers.sin_port = htons(8998);

	//socket bind
	if (bind(socketfd,(struct sockaddr *)&servers, sizeof(servers)) <0){
		perror("Binding connection error");
		return 1;
	}
	puts("Binding connection success");

	//socket listen
	listen(socketfd, 3);
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "172.17.0.1";
	char *user = "ira";
	char *password = "ira";
	char *database = "sir_db";

	conn = mysql_init(NULL);

	//connect to database
	if (!mysql_real_connect(conn, server, user, password, database, 30000, NULL, 0)){
		fprintf(stderr,"%s\n", mysql_error(conn));
		exit (1);
	}

	//end sql query
	if (mysql_query(conn,"SELECT * FROM mytable")){
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit (1);
	}

	res = mysql_use_result(conn);
	
	//show data from table
	printf ("The table from MYSQL Database: \n");

	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s %s %s \n",row[0], row[1], row[2]);

	//close connection
	mysql_free_result (res);
	mysql_close(conn);
	
	//receive incoming connection
	puts("Waiting for client connection ...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection
	client_sock = accept(socketfd, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock <0){
		perror("Accept fail");
		return 1;
	}
	puts("Connection accepted!!!");

	//Receive msg fr client
	while( (read_size = recv(client_sock, client_message, 2000, 0))>0){
		printf("Message from client: %s\n" , client_message);
		printf("[+] Sending back message ... \n");
		write(client_sock, client_message, strlen(client_message));
	}

	if (read_size == 0){
		puts("Client disconnect from server");
		fflush(stdout);
	}

	close(client_sock);
	close(socketfd);

	return 0; 
}
