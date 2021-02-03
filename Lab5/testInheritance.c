#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER 1024




int printList(char **someList)
{
	int index = 0;
	while(someList[index] != NULL)
	{
		printf("%s\n", someList[index]);
		index++;
	}
	return index;
}

int main(int argc, char **argv, char **envp)
{
	int fdout;
	ssize_t nread;
	char str[BUFFER];

	//Open output file
	fdout = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC,0644); //create file descriptor for output
	if(fdout == -1) {
		printf("Error opening output.txt\n");
		return(-1);
	}

	int pid = fork();

	//Print if parent or child:
	if(pid > 0)
	{
		wait(NULL);
		sprintf(str, "[p] this is process %d and my parent is %d\n", getpid(), getppid());

		if(write(fdout, str, strlen(str)) < strlen(str))
		{
			printf("Error writing from child to file!");
			close(fdout);
			return(-2); //error writing child
		}

		printf("\n*** PARENT PROCESS ***\nPID: %d \nArgument Count: %d\n\n", pid, argc);
	}
	else
	{
		sprintf(str, "\t[c] this is process %d and my parent is %d\n", getpid(), getppid()); //add child's line to buffer

		if(write(fdout, str, strlen(str)) < strlen(str)) //write buffer to the output.txt
		{
			printf("Error writing from child to file!");
			close(fdout);
			return(-2); //error writing child
		}

		printf("\n*** CHILD PROCESS ***\nPID: %d \nArgument Count: %d\n\n", pid, argc);
	}
	
	//Print all argv:
	printf("Arguments of current process:\n");
	printList(argv);

	printf("\n");

	//Print all ENVP:
	printf("ENVP of current process:\n");
	printList(envp);

	if(pid > 0) //Once parent is done, close the file:
	{
		close(fdout);
		printf("Wrote output.txt\n");
	}
}