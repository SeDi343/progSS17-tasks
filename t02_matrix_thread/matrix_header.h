/* !* MATRIX CALCULATION TASK - MULTITHREADING
 *
 * \description Program calculating matrixes with multithreading
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \information use: gcc -Wall matrix_task_new.c -o matrix -lm -lpthread / -fopenmp
 *
 */
 
 /* ---- SYSTEM LIBRARYS ---- */

#include <sys/time.h>
#include <sys/types.h>

/* ---- STANDARD LIBRARYS ---- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
#include <semaphore.h>

/* ---- ANSI FORMAT FOR TERMINAL ---- */
 
#define RESET         "\033[0m"
#define BLACK         "\033[30m"             /* Black */
#define RED           "\033[31m"             /* Red */
#define BOLD          "\033[1m"              /* Bold */
#define BOLDBLACK     "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED       "\033[1m\033[31m"      /* Bold Red */
#define BACKYELLOW    "\033[103m"            /* Background Yellow */
#define ITALIC        "\033[3m"              /* Italic Mode */

#define STRINGLENGTH 500
#define MAXRNDNUMBER 10

#define DEBUG 0

struct threadcode
{
	int startloop;
	int endloop;
};

struct timeval timer1, timer2;

typedef struct threadcode THREAD;

int check_number(char *number);
int clearOptarg(char *string, char *input);
void helpdesk(void);
long int matrixcalc(long int **matrix_1, long int **matrix_2, int i, int k, int value_colomn);
void *matrixcalc_thread(void *digit);
