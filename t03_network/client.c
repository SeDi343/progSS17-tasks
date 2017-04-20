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
	socklen_t adrsize;
	int ret = 0;
	char buffer[1024];
	
/*------------------------------------------------------------------*/
/* I N I T                                                          */
/*------------------------------------------------------------------*/
	
	clientsocket = socket(PF_INET, SOCK_STREAM, 0);
	if (clientsocket == -1)
	{
		perror(BOLD"\nERROR: socket:"RESET);
	}
	
}
