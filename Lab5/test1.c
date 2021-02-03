#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(int argc, char **argv, char **envp)
{
	
	printf("%d *\n", getpid());
	int pid = fork();
	fork();
	printf("%d **\n", getpid());
	fork();
	printf("%d ***\n", getpid());

	//Part E
	fork();
	printf("%d ****\n", getpid());
	fork();
	printf("%d *****\n", getpid());
	
	sleep(10);
	wait(NULL); 

	if(pid > 0)
		printf("Parent or parent(child) has closed \n");
	return EXIT_SUCCESS;

}