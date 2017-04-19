/* !* Shared Memory with Semaphores P2 - gets numbers and calculates the min, median, max
 *
 * \description A programm (P1) creates random numbers and sends it to a Shared Memory
 *              for P2, to calculate the min, median, max value of those numbers
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \information use: clang -Wall semaphore_shared_memory_P2.c -o server.out
 *
 *                   CTRL+C Handler not working currently (from Helmut)
 *                   cmpfunc from https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
 *                   RUN SERVER BEFORE CLIENT !!!!!
 */

#include "semaphore_shared_memory_header.h"

SEMUN semaphore1union;
SEMUN semaphore2union;
SEMBUF semaphore1buffer;
SEMBUF semaphore2buffer;

key_t keySemaphore;
key_t keySharedMem;

int semaphore1;
int semaphore2;
int sharedmemid;

int cmpfunc (const void * a, const void * b);
void cntrl_c_handler_server(int dummy);

int main(int argc, char *argv[])
{
	int *numberBuffer;
	
	float medianvalue = 0;
	float meanvalue = 0;
	int i = 0, z = 0, k = 0;
	
/*------------------------------------------------------------------*/
/* I N I T                                                          */
/*------------------------------------------------------------------*/
	
	keySemaphore = ftok("/etc/hostname", 'b');
	if (keySemaphore == -1)
	{
		perror(BOLD"ERROR 4: ftok error semaphore"RESET);
		exit (EXIT_FAILURE);
	}
	
	keySharedMem = ftok("/etc/hostname", 'b');
	if (keySharedMem == -1)
	{
		perror(BOLD"ERROR 15: ftok error shared mem"RESET);
		exit (EXIT_FAILURE);
	}
	
/* ---- GENERATE SHARED MEMORY ---- */
	
	sharedmemid = shmget(keySharedMem, MEMBUF, IPC_CREAT | 0666);
	if (sharedmemid < 0)
	{
		perror(BOLD"ERROR 1: shmget"RESET);
		exit (EXIT_FAILURE);
	}
	
/* ---- GENERATE SEMAPHORE 1 ---- */
	
	semaphore1 = semget(keySemaphore, 1, IPC_CREAT | 0666);
	if (semaphore1 < 0)
	{
		perror(BOLD"ERROR 2: semget 1"RESET);
		exit (EXIT_FAILURE);
	}
	
/* ---- GENERATE SEMAPHORE 2 ---- */
	
	semaphore2 = semget(keySemaphore, 1, IPC_CREAT | 0666);
	if (semaphore2 < 0)
	{
		perror(BOLD"ERROR 3: semget 2"RESET);
		exit (EXIT_FAILURE);
	}
	
	system("clear");
	
#if DEBUG
	printf(BOLDRED"Semaphore ID1: %d\n"RESET, semaphore1);
	printf(BOLDRED"Semaphore ID2: %d\n"RESET, semaphore2);
	printf(BOLDRED"Key SharedMem: %d\n"RESET, keySharedMem);
	printf(BOLDRED"Key Semaphore: %d\n"RESET, keySemaphore);
#endif
	
	printf(BOLD"Waiting for data from client...\n"RESET);
	
/*------------------------------------------------------------------*/
/* S T A R T   O F   P R O G R A M M                                */
/*------------------------------------------------------------------*/
	
	if (sharedmemid >= 0 && semaphore1 >= 0 && semaphore2 >= 0)
	{
	
/* ---- OPEN SEMAPHORE 1 ---- */
		
		semaphore1union.val = 1;
		
		if (semctl(semaphore1, 0, SETVAL, semaphore1union) < 0)
		{
			perror(BOLD"ERROR 5: can't control semaphore 1"RESET);
			exit (EXIT_FAILURE);
		}
		
/* ---- CLOSE SEMAPHORE 2 ---- */
		
		semaphore2union.val = 0;
		
		if (semctl(semaphore2, 0, SETVAL, semaphore2union) < 0)
		{
			perror(RESET"ERROR 6: can't control semaphore 2"RESET);
			exit (EXIT_FAILURE);
		}
		
/* ---- CNTRL+C HANDLER SIGNAL ---- */
		
		signal(SIGINT, cntrl_c_handler_server);
		
/* ---- ATTACH SHARED MEMORY ---- */
		
		while(1)
		{	
			numberBuffer = shmat(sharedmemid, 0, 0);
			if (numberBuffer == (int *)-1)
			{
				perror(BOLD"ERROR 10: shmat error can't attach shared memory"RESET);
				exit (EXIT_FAILURE);
			}
			
/* ---- REQUEST ACCESS TO SEMAPHORE 2 ---- */

#if DEBUG
			printf(BOLDRED"Accessing Semaphore 2...\n"RESET);
#endif
			semaphore2buffer.sem_num = 0;
			semaphore2buffer.sem_op = -1;
			semaphore2buffer.sem_flg = 0;
			
			if (semop(semaphore2, &semaphore2buffer, 1) == -1)
			{
				perror(BOLD"ERROR 11: can't unlock semaphore 2"RESET);
				exit (EXIT_FAILURE);
			}
			
/* ---- PRINT OUT EVERY NUMBER NON SORTED ---- */
			
			system("clear");
			printf("\n");
			
			printf("Numbers of array before sort\n\n");
			for (i = 0; i < MEMBUF; i++)
			{
				printf("%+03d # ", numberBuffer[i]);
			}
			
			printf("\n\n");
			
/* ---- PRINT OUT EVERY NUMBER SORTED ---- */
			
			qsort(numberBuffer, MEMBUF, sizeof(int), cmpfunc);
			
			printf("Numbers of array after sort\n\n");
			for (i = 0; i < MEMBUF; i++)
			{
				printf("%+03d # ", numberBuffer[i]);
			}
			
			printf("\n\n");
			
/* ---- MAIN USER OUTPUT ---- */
			
			printf("Minimum Value:   "BOLD"%+03d"RESET"\n", numberBuffer[0]);
			printf("Maximum Value:   "BOLD"%+03d"RESET"\n", numberBuffer[MEMBUF-1]);
			
			medianvalue = (numberBuffer[MEMBUF/2 - 1] + numberBuffer[MEMBUF/2]) / 2;
			
			printf("Median Value:    "BOLD"%+03.2f"RESET"\n", medianvalue);
			
			for (k = 0; k < MEMBUF; k++)
			{
				meanvalue = meanvalue + numberBuffer[k];
			}
			
			meanvalue = meanvalue / MEMBUF;
			
			printf("Mean Value:      "BOLD"%+03.2f"RESET"\n", meanvalue);
			
			meanvalue = 0;
			
#if DEBUG
			printf(BOLDRED"\nEverything appearing RED is a Debug Message\n"RESET);
#endif
			printf(BOLD"\nServer!\n"RESET);
			printf("Reading "BOLD"%d"RESET" random numbers\n", MEMBUF);
			printf(""BOLD"%d"RESET" arrays read from memory\n", z);
			
			z++;
			
#if DEBUG
			printf(BOLDRED"Release access to Semaphore 1...\n"RESET);
#endif
			semaphore1buffer.sem_num = 0;
			semaphore1buffer.sem_op =  1;
			semaphore1buffer.sem_flg = 0;
			
			if (semop(semaphore1, &semaphore1buffer, 1) == -1)
			{
				perror(BOLD"ERROR 12: can't unlock semaphore 1");
				exit (EXIT_FAILURE);
			}
			
			if (shmdt(numberBuffer) == -1)
			{
				perror(BOLD"ERROR 13: can't detach shared memory");
				exit (EXIT_FAILURE);
			}
		}
	}
	else
	{
		perror(BOLD"ERROR 14: Can't attach shared memory or / and semaphores");
		exit (EXIT_FAILURE);
	}
	
	exit (EXIT_SUCCESS);
}

/*------------------------------------------------------------------*/
/* F U N C T I O N S                                                */
/*------------------------------------------------------------------*/

/* ---- FUNCTION REQUESTED FOR QSORT ---- */

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

/* ---- CNTRL+c HANDLER ---- */

void cntrl_c_handler_server(int dummy)
{

	printf(BOLD"\nYou just typed CTRL+C\nServer is closing everything...\n"RESET);
	
/* ---- CLOSING SHARED MEMORY ---- */
	
	if (shmctl(sharedmemid, IPC_RMID, NULL) == -1)
	{
		perror(BOLD"\nERROR: shmctl: Can't control Shared-Memory, continue..."RESET);
	}
	
/* ---- CLOSING SEMAPHORE 1 ---- */
	
	if (semctl(semaphore1, IPC_RMID, 0) == -1)
	{
		perror(BOLD"\nERROR: semctl: Can't control Semaphore 1, continue..."RESET);
	}
	
/* ---- CLOSING SEMAPHORE 2 ---- */
	
	if (semctl(semaphore2, IPC_RMID, 0) == -1)
	{
		perror(BOLD"\nERROR: semctl: Can't control Semaphore 2, continue..."RESET);
	}
	
	printf(BOLD"If any error appeared check it manually with ipcs and remove them with ipcrm\n"RESET);
	
	exit (EXIT_SUCCESS);
}
