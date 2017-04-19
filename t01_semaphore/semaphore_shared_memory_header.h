/* ---- SYSTEM BASED LIBRARYS ---- */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

/* ---- STANDARD LIBRARYS ---- */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

/* ---- ANSI FORMAT FOR TERMINAL ---- */

#define RESET         "\033[0m"
#define RED           "\033[31m"             /* Red */
#define BOLD          "\033[1m"              /* Bold */
#define BOLDRED       "\033[1m\033[31m"      /* Bold Red */
#define ITALIC        "\033[3m"              /* Italic Mode */


#define MEMBUF 128
#define DEBUG 0

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

typedef union semun SEMUN;
typedef struct sembuf SEMBUF;
