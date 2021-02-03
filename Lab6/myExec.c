#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	printf("Exec.c PID: %d\n",getpid());
	printf("Exec.c PPID: %d\n",getppid());

	//part c
	for(char **env=envp; *env !=0;env++)
	{
		char *thisEnv = *env;
	
		printf("%s\n",thisEnv);
	}



	
	exit(0);

}
