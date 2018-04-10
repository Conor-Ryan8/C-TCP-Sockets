/*******************************************************************************
 * Conor Ryan - Socket Programming					       *
 * Basic TCP Server 							       *
 * March 2018			       				               *
 *******************************************************************************/

//Header for bzero
#include <string.h>
//Header for exit
#include <stdlib.h>
//Header for read/write
#include <unistd.h>
//Header for printf
#include <stdio.h>
//Header for sockets
#include <netinet/in.h>

//Error function to display error messages
void error (char *msg)
{
	//Print the message passed to the function
	printf("%s",msg);

	//Exit the program
	exit(1);
}
//Main Function
int main (int argc, char *argv[]){

	//Variables to store port number and status values
	int sock, newsock, port, status;

	//Structure to hold connection information
	struct sockaddr_in server, client;

	//Array of characters to hold data sent/recieved
	char buffer [256];

	//Integer to store length of client & server structures
	int slength = sizeof(server);
	int clength = sizeof(client);

	//Checks the program is given 2 arguements when run
	if (argc < 2)

		//Sends error message to error function
		error("To use: ./TCPServer PortNo\n");

	//Converts arguement 1 from string to integer and stores as "port"
	port = atoi(argv[1]);

	//Attempts to create socket and passes status value to "sock"
	sock = socket(AF_INET, SOCK_STREAM, 0);

	//Checks if socket creation worked by reading the status value in "sock"
	if (sock < 0)

		//Sends error message to error function
		error("Error opening socket!\n");

	//Zeroes server structure and slength integer
	bzero((char *) &server, slength);

	//Sets connection type as internet in family field of the serverstructure
	server.sin_family = AF_INET;

	//Takes value in "port", converts to network byte order and adds into port field of the server structure
	server.sin_port = htons(port);

	//Sets incoming address in the server structure to any
	server.sin_addr.s_addr = INADDR_ANY;

	//Attempts to bind the socket, passing status value to "sock", then checks "sock" isnt empty
	if (bind(sock, (struct sockaddr *) &server, slength) < 0)

		//Sends error message to error function
		error("Error on binding!\n");

	//Listens to the socket for incoming data, holds until it finds some
	listen(sock,5);

	//When the socket finds data attempt to accept it, and store status value in "newsock"
	newsock = accept(sock, (struct sockaddr *) &client, &clength);

	//Check to see if the accept call worked by reading the status value "newsock"
	if (newsock < 0)

		//Sends error message to error function
		error("Error on accept!\n");

	//Empties the buffer
	bzero(buffer,256);

	//Attempt to read from the socket and store data in the buffer, and status value in "status"
	status = read(newsock,buffer,255);

	//Checks to see if the read worked by reading the status value in "status"
	if (status < 0)

		//Sends error message to error function
		error("Error reading from socket!\n");

	//Prints the message recived from the client stored in the buffer
	printf("\nMessage Recieved: %s\n",buffer);

	//Attempt to write a confirmation message to the socket and store status value in "status"
	status = write(newsock,"\nMessage Recieved by Server\n",30);

	//Checks to see if the write worked by reading the status value in "status"
	if (status < 0)

		//Sends error message to error function
		error("Error writing to socket!\n");

	//Returns 0 for the lols
	return 0;
}

