/***********************************************************************************
*	Lab 06 - Part 1
*
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#include <sys/wait.h>

#define COUNT 1000
#define PERM 0644

int main(int argc, char *argv[])
{
	int index = 0;
	time_t now;
	int value;
	pid_t C1, C2;
	char outBuffer[128];
	int outFD;
	int waitRV;

	if (argc < 2)
	{
		printf("You need a file to write to ...\n");
		return -1;
	}

	//seed the random number with different values at different times
	srand((unsigned)time(&now));
	//srand(10);
	//Generate random numbers that are less than 100
	value = rand() % 100;

	if ((outFD = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, PERM)) == -1)
	{
		printf("Error opening file: %s\n", argv[1]);
		return (-1);
	}

	sprintf(outBuffer, "Parent process: my value is %d and my index is %d \r\n\r\n", value, index);
	write(outFD, outBuffer, strlen(outBuffer));

	C1 = fork();
	if (C1 < 0)
	{
		printf("Error: fork 1 failed\n");
		return -2;
	}

	if (C1 == 0)
	{
		for (index = 1; index <= COUNT; index++)
		{
			sprintf(outBuffer, "Child 1: my value is %d and my index is %d \r\n", value, index);
			//printf("Child 1: my value is %d and my index is %d \r\n", value, index);
			write(outFD, outBuffer, strlen(outBuffer));
			value++;
		}
	}

	else
	{
		waitRV = wait(&C1);
		if (C2 < 0)
		{
			printf("Error: fork 1 failed\n");
			return -2;
		}

		if (C2 == 0)
		{
			for (index = 1; index <= COUNT; index++)
			{
				sprintf(outBuffer, "\tChild 2: my value is %d and my index is %d \r\n", value, index);
				//printf("Child 2: my value is %d and my index is %d \r\n", value, index);
				write(outFD, outBuffer, strlen(outBuffer));
				value++;
			}
		}
		else
		{
			wait(0);
			wait(0);
			close(outFD);
		}
	}

	printf("process %d terminated\n", getpid());
	return 0;
}
