//Header used for bzero
#include <string.h>
//Header used for exit
#include <stdlib.h>
//Header used for read/write
#include <unistd.h>
//Header used for printf
#include <stdio.h>



//#include <netinet/in.h>

void error (char *msg){
	printf("%s",msg);
	exit(1);}

int main (int argc, char *argv[]){
	int sockfd, newsockfd, portno, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2)
		error("NO port provided\n");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket!\n");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding!\n");

	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0)
		error("ERROR on accept!\n");

	bzero(buffer,256);
	n = read(newsockfd,buffer,255);

	if (n < 0)
		error("ERROR reading from socket!\n");

	printf("Message Recieved: %s\n",buffer);
	n = write(newsockfd,"Message Recieved by Server\n",26);

	if (n < 0)
		error("ERROR writing to socket!\n");

	return 0;}

