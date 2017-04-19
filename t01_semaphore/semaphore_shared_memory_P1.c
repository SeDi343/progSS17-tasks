/* !* Shared Memory with Semaphores P1 - creates numbers and sends it to P2
 *
 * \description A programm (P1) creates random numbers and sends it to a Shared Memory
 *              for P2, to calculate the min, median, max value of those numbers
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \information use: clang -Wall semaphore_shared_memory_P1.c -o client.out
 *
 *                   CTRL+C Handler not working currently (from Helmut)
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

void cntrl_c_handler_client(int dummy);

int main(int argc, char *argv[])
{
	int *numberBuffer;
	
	int i = 0, z = 0;
	
	time_t t;
	
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
	
	printf(BOLD"Start server before client!\n"RESET);
	
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
			perror(BOLD"ERROR 6: can't control semaphore 2"RESET);
			exit (EXIT_FAILURE);
		}
		
/* ---- CNTRL+C HANDLER SIGNAL ---- */
		
		signal(SIGINT, cntrl_c_handler_client);
		
/* ---- FILL MEMORY WITH RANDOM VALUES ---- */
		
		time(&t);
		srand((unsigned int) t);
		
/* ---- ATTACH SHARED MEMORY ---- */
		
		while(1)
		{
			numberBuffer = shmat(sharedmemid, 0, 0);
			if (numberBuffer == (int *)-1)
			{
				perror(BOLD"ERROR 10: shmat error can't attach shared memory"RESET);
				exit (EXIT_FAILURE);
			}
			
/* ---- REQUEST ACCESS TO SEMAPHORE 1 ---- */
			
#if DEBUG
			printf(BOLDRED"Accessing Semaphore 1...\n"RESET);
#endif
			semaphore1buffer.sem_num = 0;
			semaphore1buffer.sem_op = -1;
			semaphore1buffer.sem_flg = 0;
			
			if (semop(semaphore1, &semaphore1buffer, 1) == -1)
			{
				perror(BOLD"ERROR 11: can't unlock semaphore 1"RESET);
				exit (EXIT_FAILURE);
			}
			
/* ---- FILL SHARED MEMORY WITH RANDOM NUMBERS ---- */
			
			printf("\n");
			
			for (i = 0; i < MEMBUF; i++)
			{
				numberBuffer[i] = (rand()%61-20);
				printf("%+03d # ", numberBuffer[i]);
			}
			
			printf("\n");
			
/* ---- USER OUTPUT ---- */
			
			z++;
			
#if DEBUG
			printf(BOLDRED"\nEverything appearing RED is a Debug Message\n"RESET);
#endif
			printf(BOLD"\nClient!\n"RESET);
			printf("Generating "BOLD"%d"RESET" random numbers\n", MEMBUF);
			printf(""BOLD"%d"RESET" arrays written into memory\n\n", z);
			
/* ---- WAIT FOR NEXT OPERATION AND CLEAR SCREEN ---- */
			
#if DEBUG
			printf(BOLDRED"Sleep 1 sec\n"RESET);
#endif
			sleep(1);
			system("clear");
			
/* ---- RELEASE ACCESS TO SEMAPHORE 2 ---- */

#if DEBUG
			printf(BOLDRED"Release access to Semaphore 2\n"RESET);
#endif
			semaphore2buffer.sem_num = 0;
			semaphore2buffer.sem_op =  1;
			semaphore2buffer.sem_flg = 0;
			
			if (semop(semaphore2, &semaphore2buffer, 1) == -1)
			{
				perror(BOLD"ERROR 12: can't unlock semaphore 2"RESET);
				exit (EXIT_FAILURE);
			}
			
/* ---- DETACH SHARED MEMORY ---- */
			
			if (shmdt(numberBuffer) == -1)
			{
				perror(BOLD"ERROR 13: can't detach from shared memory"RESET);
				exit (EXIT_FAILURE);
			}
		}
	}
	else
	{
		perror(BOLD"ERROR 14: Can't attach shared memory or / and semaphores"RESET);
		exit (EXIT_FAILURE);
	}
	
	exit (EXIT_SUCCESS);
}

/*------------------------------------------------------------------*/
/* F U N C T I O N S                                                */
/*------------------------------------------------------------------*/

/* ---- CNTRL+C HANDLER ---- */

void cntrl_c_handler_client(int dummy)
{
	printf(BOLD"\nYou just typed CTRL+C\nClient is closing connection...\n"RESET);
	
/* ---- REQUESTING ACCESS TO SEMAPHORE 2 ---- */
	
	semaphore2buffer.sem_num = 0;
	semaphore2buffer.sem_op = -1;
	semaphore2buffer.sem_flg = IPC_NOWAIT;
	
	if (semop(semaphore2, &semaphore2buffer, 1) == -1)
	{
		perror(BOLD"\nERROR: semop: Can't lock Semaphore 2"RESET);
	}
	
	exit (EXIT_SUCCESS);
}
