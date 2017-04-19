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
 *              Use: telnet 127.0.0.1 PORTNUMBER
 */

#include "myhead.h"

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr, cliaddr;
	pid_t ForkPID;
	socklen_t len;
	int optval = 1;
	int ret = 0;
	
/*------------------------------------------------------------------*/
/* I N I T                                                          */
/*------------------------------------------------------------------*/
	
/* ---- SIGCHLD signal handler that deals with zombies ---- */
	
	install_SIGCHLD_handler();
	
/* ---- socket() open a file desciptor ---- */
	
	listenfd = socket(PF_INET, SOCK_STREAM, 0);
	if (listenfd == -1)
	{
		perror(BOLD"\nERROR: socket:"RESET);
	}
	
/* ---- setsockopt() free previosly used sockets() ---- */
	
	ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (ret == -1)
	{
		perror(BOLD"\nERROR: setsockopt:"RESET);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = PF_INET; /* using IPv4 */
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* htonl convert values between host and network byte order */
	servaddr.sin_port = htons(PORTNUMBER); /* htons convert values between host and network byte order */
	
/* ---- bind() ---- */
	
	ret = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (ret == -1)
	{
		perror(BOLD"\nERROR: bind:"RESET);
	}
	
/* ---- listen() ---- */
	
	ret = listen(listenfd, 5);
	if (ret == -1)
	{
		perror(BOLD"\nERROR: listen:"RESET);
	}
	
/*------------------------------------------------------------------*/
/* P R O G R A M M   S T A R T                                      */
/*------------------------------------------------------------------*/
	
	while(1)
	{
		len = sizeof(cliaddr);
		
/* ---- accept() ---- */
		
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
		if (connfd == -1)
		{
			perror(BOLD"\nERROR: accept:"RESET);
		}
		
/* ---- Let child process handle the connection ---- */
		
		ForkPID = fork();
		
/* ---- Child process ---- */
		
		if (ForkPID == 0)
		{
			close(listenfd); /* close listen port */
			
			dup2(connfd, 0); /* redirect STDIN */
			dup2(connfd, 1); /* redirect STDOUT */
			
/* ---- Run a STDIN/STDOUT application ---- */
			
			ret = execlp("./program", "program", (char *)NULL);
			if (ret == -1)
			{
				perror(BOLD"\nERROR: execlp:"RESET);
			}
		}
		
/* ---- Parent process ---- */
		
		else
		{
			close (connfd);
		}	
	}
}

/* Below is the singal handler to avoid zombie processes as
 * well as the appropriate installer
 *
 * SIGCHLD handler, derived from W. Richard Stevens,
 * Network Programming, Vol.1, 2nd Edition, p128
 */

void SIGCHLD_handler(int signo)
{
	pid_t pid;
	int stat;
	
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		;
	}
	return;
}

/* ---- Installer for the SIGCHLD handler ---- */

void install_SIGCHLD_handler(void)
{
	struct sigaction act;
	
/* ---- Block all signals during exec of SIGCHLD_handler ---- */
	
	sigfillset(&act.sa_mask);
	act.sa_handler = &SIGCHLD_handler;
	
/* ---- Auto restart interrupted system calls ---- */
	
	act.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);
}
