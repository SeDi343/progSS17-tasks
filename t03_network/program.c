/* !* SERVER EXECUTING PROGRAM TASK
 *
 * \description Server application to run programs over network
 *
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 19.04.2017 - Created
 *          Rev.: 02, 19.04.2017 - Using Horauers code
 *
 * \information Find Code source on
 *              https://cis.technikum-wien.at/documents/bel/2/sua/semesterplan/notes/download/nwprog/nwprog.html#_client_server_program
 *
 */

#include "myhead.h"

int main(void)
{
	char buf[80];
	char ans[80];
	int readlen;
	
	while (strncmp(ans, "42", 2) != 0)
	{
		sprintf(buf, "What's the answer to god, the universe and everything? ");
		write(1, buf, strlen(buf));
		
		readlen = read(0, ans, 5);
		ans[readlen] = '\0';
		
		if (strncmp(ans, "42", 2) == 0)
		{
			sprintf(buf, "\n\nHoly Zarquon Singingfish - "BOLD"you got it."RESET"\n\n");
			write(1, buf, strlen(buf));
		}
		else
		{
			sprintf(buf, "\n\nBelgium monkeyman; "BOLD"go sit in a corner and sing to your cat."RESET"\n\n");
			write(1, buf, strlen(buf));
		}
	}
	
	exit(0);
}
