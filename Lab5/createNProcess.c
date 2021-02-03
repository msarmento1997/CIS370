#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int n;
	int i;
	pid_t cpid;

	if(argc ==2)
	{
		n= atoi(argv[1]);

		for(i=0; i<n; i++)
		{
			if(fork() ==0)
			{
				printf("[c] this is the child process %d, my pid is %d\n",i,getpid());
				sleep(3);
				
				exit(i);
			}

		}


		for(i = 0; i<n; i++)
		{ 
			int status;
			cpid = wait(&status);

			printf("[p] child %d (pid = %d) just exited!\n",WEXITSTATUS(status),cpid);
		}

		printf("I am the parent process (pid = %d) and all my child processes exited!\n",getpid());
	}else
	{
		printf("argument list is empty.\n");
	}




}