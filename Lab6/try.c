#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	pid = fork();

	if(pid<0)
	{
		printf("error\n");
	}
	else if(pid == 0)
	{
		execlp("./part1 output.txt", "./part1 output.txt", NULL);
	}
	else
	{
		wait(NULL);
		printf("CHILD Complete\n");
	}
}