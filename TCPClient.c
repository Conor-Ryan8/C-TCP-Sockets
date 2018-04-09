/*******************************************************************************
 * Conor Ryan - Socket Programming					       *
 * Basic TCP Client 							       *
 * March 2018			       				               *
 *******************************************************************************/

//Header used for bzero
#include <string.h>
//Header used for exit
#include <stdlib.h>
//Header used for read/write
#include <unistd.h>
//Header used for printf
#include <stdio.h>
//Header used for sockets
#include <netdb.h>

//Error function to display error messages
void error (char *msg)
{
	printf("%s",msg);
	exit(0);
}
//Main Function
int main (int argc, char *argv[])
{
	int sock, port, status;
	struct sockaddr_in server;
	struct hostent *serv;
	char buffer [256];
	int slength = sizeof(server);

	if (argc < 3)
		error("To use: ./TCPClient IPAddress PortNo\n");

	port = atoi(argv[2]);
	serv = gethostbyname(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
		error("Error opening socket!\n");

	if (serv == NULL)
		error("No such host!\n");

	bzero((char *) &server, slength);
	server.sin_family = AF_INET;
	bcopy((char *)serv->h_addr, (char *)&server.sin_addr.s_addr, serv->h_length);
	server.sin_port = htons(port);

	if (connect(sock,(struct sockaddr *)&server, slength) < 0)
		error("Error Connecting!\n");

	printf("\nPlease enter message: ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	status = write(sock,buffer,strlen(buffer));

	if (status < 0)
		error("ERROR writing to socket!\n");

	bzero(buffer,256);
	status = read(sock,buffer,255);

	if (status < 0)
		error("ERROR reading from socket!\n");

	printf("%s\n",buffer);
	return 0;}
