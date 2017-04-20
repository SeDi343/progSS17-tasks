/* !* SERVER EXECUTING PROGRAM TASK
 *
 * \description Client application to communicate with server
 *
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 20.04.2017 - Created
 *
 * \information
 *
 */

#include "myhead.h"

int main(int argc, char *argv[])
{
	int clientsocket;
	struct sockaddr_in clientaddr;
	socklen_t addrsize;
	char buffer[MEMSIZE];
	
/*------------------------------------------------------------------*/
/* I N I T                                                          */
/*------------------------------------------------------------------*/
	
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_addr.s_addr = inet_addr(HOSTNAME);
	clientaddr.sin_port = htons(PORTNUMBER);
	
	memset(clientaddr.sin_zero, '\0', sizeof(clientaddr.sin_zero));
	
	clientsocket = socket(PF_INET, SOCK_STREAM, 0);
	if (clientsocket == -1)
	{
		perror(BOLD"\nERROR: socket:"RESET);
	}
	
/*------------------------------------------------------------------*/
/* C O N N E C T                                                    */
/*------------------------------------------------------------------*/
	
	addrsize = sizeof(clientaddr);
	
	if (connect(clientsocket, (struct sockaddr *) &clientaddr, addrsize) == -1)
	{
		perror(BOLD"\nERROR: connecting:"RESET);
	}
	
	while(1)
	{
		memset(buffer, '\0', sizeof(buffer));
		recv(clientsocket, buffer, MEMSIZE, 0);
		printf("%s", buffer);
		
		if (strncmp(buffer, "Holy Zarquon Singingfish - you got it.", 38) == 0)
		{
			exit(EXIT_SUCCESS);
		}
		
		memset(buffer, '\0', sizeof(buffer));
		scanf("%s", buffer);
		send(clientsocket, buffer, MEMSIZE, 0);
	}
}
