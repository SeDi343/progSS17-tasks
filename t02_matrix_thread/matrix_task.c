/* !* MATRIX CALCULATION TASK - MULTITHREADING
 *
 * \description Program calculating matrixes with multithreading
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \information use:
 *                  TASK 1-2   gcc -Wall matrix_task.c -o matrix -lm
 *                  TASK 3     gcc -Wall matrix_task.c -o matrix -lm -lpthread
 *                  TASK 4     gcc -Wall matrix_task.c -o matrix -lm -fopenmp
 *
 *                  Change preprocessor variables for different tasks!
 *
 */

#include "matrix_header.h"

#define TASK1 0
#define TASK3 1
#define TASK4 0

long int **matrix_1, **matrix_2, **matrix_3;
int value_row = 20;
int value_colomn = 20;

int main(int argc, char *argv[])
{
	char numberString[STRINGLENGTH];
	int error = 0;
	int i, k;
	int opt;
	char *pEnd;
	
#if TASK3
	THREAD *MatrixThread1 = (THREAD *)malloc(sizeof(THREAD));
	THREAD *MatrixThread2 = (THREAD *)malloc(sizeof(THREAD));
	THREAD *MatrixThread3 = (THREAD *)malloc(sizeof(THREAD));
	THREAD *MatrixThread4 = (THREAD *)malloc(sizeof(THREAD));
	
	pthread_t thread_1, thread_2, thread_3, thread_4;
#endif
	
#if TASK4
	omp_set_num_threads(4);
#endif
	
/* ---- PARAMETER INPUT ---- */
	
	while ((opt = getopt (argc, argv, "n:?")) != -1)
	{
		switch (opt)
		{
			case 'n':
				error = clearOptarg(numberString, optarg);
				error = check_number(numberString);
				
				value_row = strtod(numberString, &pEnd);
				value_colomn = value_row;
			break;
			
			case '?':
				system("clear");
				helpdesk();
				
				exit(EXIT_SUCCESS);
			break;
		}
	}
	
	helpdesk();
	
	if (error == 1)
	{
		perror(BOLD"\nERROR: Parameter: One or more parameters are not correct"RESET);
		exit(EXIT_FAILURE);
	}
	
/* ---- MALLOC THE ROWS ---- */
	
	matrix_1 = (long int **)malloc(value_row * sizeof(long int *));
	if (matrix_1 == NULL)
	{
		perror(BOLD"\nERROR: malloc: cant malloc matrix1 row"RESET);
		exit(EXIT_FAILURE);
	}
	matrix_2 = (long int **)malloc(value_row * sizeof(long int *));
	if (matrix_2 == NULL)
	{
		perror(BOLD"\nERROR: malloc: cant malloc matrix2 row"RESET);
		exit(EXIT_FAILURE);
	}
	matrix_3 = (long int **)malloc(value_row * sizeof(long int *));
	if (matrix_3 == NULL)
	{
		perror(BOLD"\nERROR: malloc: cant malloc matrix3 row"RESET);
		exit(EXIT_FAILURE);
	}
	
/* ---- MALLOC THE COLOMNS ---- */
	
	for (i = 0; i < value_row; i++)
	{
		matrix_1[i] = (long int *)malloc(value_colomn * sizeof(long int));
		if (matrix_1[i] == NULL)
		{
			perror(BOLD"\nERROR: malloc: cant malloc matrix1 colomn"RESET);
			exit(EXIT_FAILURE);
		}
		matrix_2[i] = (long int *)malloc(value_colomn * sizeof(long int));
		if (matrix_2[i] == NULL)
		{
			perror(BOLD"\nERROR: malloc: cant malloc matrix2 colomn"RESET);
			exit(EXIT_FAILURE);
		}
		matrix_3[i] = (long int *)malloc(value_colomn * sizeof(long int));
		if (matrix_3[i] == NULL)
		{
			perror(BOLD"\nERROR: malloc: cant malloc matrix3 colomn"RESET);
			exit(EXIT_FAILURE);
		}
	}
	
/* ---- GENERATING MATRIX1 WITH RANDOM VALUES ---- */
	
	srand(time(NULL));
	
	for (i = 0; i < value_row; i++)
	{
	
#if DEBUG
	printf("| ");
#endif
	
		for (k = 0; k < value_colomn; k++)
		{
			matrix_1[i][k] = rand()%MAXRNDNUMBER;
			
#if DEBUG
			printf(BOLD"%ld "RESET, matrix_1[i][k]);
#endif

		}

#if DEBUG
		printf("|\n");
#endif

	}
	
#if DEBUG
	printf("\n");
#endif
	
/* ---- GENERATING MATRIX2 WITH RANDOM VALUES ---- */
	
	for (i = 0; i < value_row; i++)
	{
	
#if DEBUG
	printf("| ");
#endif
	
		for (k = 0; k < value_colomn; k++)
		{
			matrix_2[i][k] = rand()%MAXRNDNUMBER;
			
#if DEBUG
			printf(BOLD"%ld "RESET, matrix_2[i][k]);
#endif

		}

#if DEBUG
		printf("|\n");
#endif

	}
	
	printf(ITALIC"Generated Matrix 1 with "BOLD ITALIC"%d"ITALIC"x"BOLD ITALIC"%d"ITALIC" values.\n"RESET, value_row, value_colomn);
	printf(ITALIC"Generated Matrix 2 with "BOLD ITALIC"%d"ITALIC"x"BOLD ITALIC"%d"ITALIC" values.\n"RESET, value_row, value_colomn);
	
/*------------------------------------------------------------------*/
/* TASK1: CALCULATE MATRIX WITHOUT THREADS                          */
/*------------------------------------------------------------------*/
	
#if TASK1
	
	printf(BOLD ITALIC"\n\nTASK 1: CALCULATION WITHOUT THREADS\n"RESET);
	gettimeofday(&timer1, NULL);
	
	for (i = 0; i < value_row; i++)
	{
		
#if DEBUG
		printf("| ");
#endif
		
		for (k = 0; k < value_colomn; k++)
		{
			matrix_3[i][k] = 0;
			
			matrix_3[i][k] = matrixcalc(matrix_1, matrix_2, i, k, value_colomn);
			
#if DEBUG
			printf(BOLD"%3ld "RESET, matrix_3[i][k]);
#endif

		}
		
#if DEBUG
		printf("|\n");
#endif
		
	}
	
	gettimeofday(&timer2, NULL);
	
	printf("\nMultiplicated 2 Matrixes with "BOLD"%dx%d"RESET" values.\n", value_row, value_colomn);
	printf(BACKYELLOW BLACK ITALIC"Calculation needed "BACKYELLOW BOLDBLACK"%f"RESET BACKYELLOW BLACK ITALIC" secs."RESET"\n\n", ((timer2.tv_sec+timer2.tv_usec*0.000001)-(timer1.tv_sec+timer1.tv_usec*0.000001)));
	
#endif /* TASK1 */

/*------------------------------------------------------------------*/
/* TASK3: CALCULATE MATRIX WITH THREADS WITH PTHREADS               */
/*------------------------------------------------------------------*/
	
#if TASK3
	
	printf(BOLD ITALIC"\n\nTASK 3: CALCULATION WITH PTHREADS\n"RESET);
	gettimeofday(&timer1, NULL);
	
	MatrixThread1->startloop = 0;
	MatrixThread1->endloop = value_row/4;
	
	MatrixThread2->startloop = MatrixThread1->endloop;
	MatrixThread2->endloop = value_row/2;
	
	MatrixThread3->startloop = MatrixThread2->endloop;
	MatrixThread3->endloop = value_row/2 + value_row/4;
	
	MatrixThread4->startloop = MatrixThread3->endloop;
	MatrixThread4->endloop = value_row;
	
	pthread_create(&thread_1, NULL, matrixcalc_thread, MatrixThread1);
	pthread_create(&thread_2, NULL, matrixcalc_thread, MatrixThread2);
	pthread_create(&thread_3, NULL, matrixcalc_thread, MatrixThread3);
	pthread_create(&thread_4, NULL, matrixcalc_thread, MatrixThread4);
	
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL); 
	pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);
	
	gettimeofday(&timer2, NULL);
	
	printf("\nMultiplicated 2 Matrixes with "BOLD"%dx%d"RESET" values.\n", value_row, value_colomn);
	printf(BACKYELLOW BLACK ITALIC"Calculation needed "BACKYELLOW BOLDBLACK"%f"RESET BACKYELLOW BLACK ITALIC" secs."RESET"\n\n", ((timer2.tv_sec+timer2.tv_usec*0.000001)-(timer1.tv_sec+timer1.tv_usec*0.000001)));
	
	
#endif /* TASK3 */

/*------------------------------------------------------------------*/
/* TASK4: CALCULATE MATRIX WITH THREADS WITH OMP                    */
/*------------------------------------------------------------------*/

#if TASK4
	
	printf(BOLD ITALIC"\n\nTASK 4: CALCULATION WITH OMP LIBRARAY\n"RESET);
	gettimeofday(&timer1, NULL);
	
	for (i = 0; i < value_row; i++)
	{
	
#if DEBUG
		printf("| ");
#endif
		#pragma omp parallel for
		for(k = 0; k < value_colomn; k++)
		{
			matrix_3[i][k] = 0;
			
			matrix_3[i][k] = matrixcalc(matrix_1, matrix_2, i, k, value_colomn);
			
#if DEBUG
			printf(BOLD"%3ld "RESET, matrix_3[i][k]);
#endif
		}
	
#if DEBUG
		printf("|\n");
#endif
	}
	
	gettimeofday(&timer2, NULL);
	
	printf("\nMultiplicated 2 Matrixes with "BOLD"%dx%d"RESET" values.\n", value_row, value_colomn);
	printf(BACKYELLOW BLACK ITALIC"Calculation needed "BACKYELLOW BOLDBLACK"%f"RESET BACKYELLOW BLACK ITALIC" secs."RESET"\n\n", ((timer2.tv_sec+timer2.tv_usec*0.000001)-(timer1.tv_sec+timer1.tv_usec*0.000001)));
	
#endif /* TASK 4 */
	
	for (i = 0; i < value_row; i++)
	{
		free(matrix_1[i]);
		free(matrix_2[i]);
		free(matrix_3[i]);
	}
	
	free(matrix_1);
	free(matrix_2);
	free(matrix_3);
	
#if TASK3
	free(MatrixThread1);
	free(MatrixThread2);
	free(MatrixThread3);
	free(MatrixThread4);
#endif
	
	exit(EXIT_SUCCESS);
}

/*------------------------------------------------------------------*/
/* F U N C T I O N S                                                */
/*------------------------------------------------------------------*/

#if TASK1 || TASK4

long int matrixcalc(long int **matrix_1, long int **matrix_2, int i, int k, int value_colomn)
{
	long int matrix = 0;
	int j;
	
	for (j = 0; j < value_colomn; j++)
	{
		matrix = matrix + (matrix_1[i][j] * matrix_2[j][k]);
	}
	
	return matrix;
}

#endif

#if TASK3

void *matrixcalc_thread(void *digit)
{
	long int result = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	THREAD *digitcode = (THREAD *)digit;
	
	for (i = digitcode->startloop; i < digitcode->endloop; i++)
	{
		for (j = 0; j < value_row; j++)
		{
			for (k = 0; k < value_colomn; k++)
			{
				result = result + (matrix_1[i][k] * matrix_2[k][j]);
			}
			
			matrix_3[i][j] = result;
			result = 0;
		}
	}
	
	pthread_exit(0);
}

#endif

/* ---- ONLY NUMBERS FUNCTION ---- */

int check_number(char *number)
{
	char * pch;
	int i;
	
	pch = strchr(number, '.');
	if (pch != NULL)
	{
		printf(BOLD"\nERROR: No floating-point numbers allowed.\n"RESET);
		return 1;
	}
	
	pch = strchr(number, ',');
	if (pch != NULL)
	{
		printf(BOLD"\nERROR: No floating-point numbers allowed.\n"RESET);
		return 1;
	}
	
	for (i = 0; i < strnlen(number, STRINGLENGTH); i++)
	{
		if (isdigit(number[i]) == 0)
		{
			printf(BOLD"\nERROR: Parameter is not a number.\n"RESET);
			return 1;
		}
	}
	
	return 0;
}

/* ---- FUNCTION TO AVOID STRINGLEAKS IN MAIN FILE ---- */

int clearOptarg(char *string, char *input)
{
	strncpy(string, input, strnlen(input, STRINGLENGTH));
	string[strlen(input)] = '\0';
	
	if (strlen(string) >= STRINGLENGTH)
	{
		printf(BOLD"\nERROR: Parameterinput is too long!\n"RESET);
		return 1;
	}
	else
	{
		return 0;
	}
}

/* ---- HELPDESK ---- */

void helpdesk(void)
{
	system("clear");
	printf(BOLD"\nMATRIX MULTIPLICATION PROGRAM @ V1.0\n"RESET);
	printf(BOLD"Created by Sebastian Dichler <el16b032@technikum-wien.at>\n\n"RESET);
	printf("Change between Task with Preprocessor Variables!\n\n");
	printf(BOLD ITALIC"PARAMETER INPUT\n"RESET);
	printf(""BOLD"[-n]"RESET"  Number of matrix size.\n\n");
}
