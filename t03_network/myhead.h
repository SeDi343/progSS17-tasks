/* !* HEADER FILE FOR SERVER EXECUTING PROGRAM TASK
 *
 * \description Header file for server executing program task
 *
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 19.04.2017 - Created
 *
 * \information changed Port to 8888 (default 6778)
 *
 */

#ifndef _myhead_
#define _myhead_

/* ---- SYSTEM BASED LIBRARYS ---- */

#include <sys/socket.h>
#include <sys/types.h> /* needed for some BSD versions */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

/* ---- STANDARD LIBRARYS ---- */

#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define DEBUG 1
#define PORTNUMBER 8888 /* check "/etc/services" */
#define HOSTNAME "127.0.0.1"
#define MEMSIZE 1204

/* ---- ANSI FORMAT FOR TERMINAL ---- */

#define RESET         "\033[0m"
#define BLACK         "\033[30m"             /* Black */
#define RED           "\033[31m"             /* Red */
#define GREEN         "\033[32m"             /* Green */
#define CYAN          "\033[36m"             /* Cyan */

#define BOLD          "\033[1m"              /* Bold */
#define BOLDRED       "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN     "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLACK     "\033[1m\033[30m"      /* Bold Black */
#define BOLDCYAN      "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE     "\033[1m\033[37m"      /* Bold White */

#define BACKBLACK     "\033[100m"            /* Background Black */
#define BACKRED       "\033[101m"            /* Background Red */
#define BACKGREEN     "\033[102m"            /* Background Green */
#define BACKYELLOW    "\033[103m"            /* Background Yellow */
#define BACKBLUE      "\033[104m"            /* Background Blue */
#define BACKMAGENTA   "\033[105m"            /* Background Magenta */
#define BACKCYAN      "\033[106m"            /* Background Cyan */
#define BACKWHITE     "\033[107m"            /* Background White */

#define ITALIC        "\033[3m"              /* Italic Mode */

void SIGCHLD_handler(int);
void install_SIGCHLD_handler(void);

#endif /* _myhead_ */
