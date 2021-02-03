#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

	char *cmd[] = {"pwd", "ls", "date", "ps", "top"};
	int i;
	while(1)
	{	
		printf("0=pwd, 1=ls, 2=date, 3=ps, 4=top : ");
		scanf("%d", &i);
		

		if(fork() == 0)
		{
			execlp(cmd[i],cmd[i],NULL);
			printf("command not found\n");
		}
		//printf("0=pwd, 1=ls, 2=date, 3=ps, 4=top : ");
		//scanf("%d", &i);
		//execlp(cmd[i],cmd[i],NULL);
		//printf("command not found\n");

		else 
		{
			wait(0);
			continue;
		}

	}




}