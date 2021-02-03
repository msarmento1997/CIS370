#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER 1024
int main(int argc, char **argv, char **envp)
{
	pid_t pid;

	
/*
	//part a

	pid = fork();
	if(pid < 0)
	{
		printf("Error: Fork failed\n");
	}
	else if(pid == 0)
	{
		printf("PID: %d\n",getpid());
		printf("PPID: %d\n",getppid());
		execlp("./myExec", "myExec", NULL);
		printf("Error with execlp\n");
	}
*/
/*
	//part b
	 int fdout;

	 char str[BUFFER];

	fdout = open("file1.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
	pid = fork();
	if(pid < 0)
	{
		printf("Error with fork.\n");
		close(fdout);
	}
	else if(pid == 0)
	{
		sprintf(str, "PID : %d and PPID : %d",getpid(),getppid());
		if(write(fdout, str, strlen(str))<strlen(str))
		{
			printf("Error writing to file.\n");
			close(fdout);
		}
	}
	close(fdout);
	*/

	//part c

	strcpy(envp[1], "MichaelSarmento");

	for(char **env=envp; *env !=0;env++)
	{
		char *thisEnv = *env;
		execle("./myExec",thisEnv ,  (char *)0, envp);
		//printf("%s\n",thisEnv);
	}

	

	return 0;







}
