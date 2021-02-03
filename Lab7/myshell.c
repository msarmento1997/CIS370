#include <stdio.h>

#include<string.h>

#include<stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

int main()

{

	char buff[100];

	char *p;

	char *args[10];

	int count=0,pid,i;

	while(1)

	{


		printf("myShell>");
		
		fgets(buff,sizeof(buff),stdin);

		//eliminate /n in buff

		buff[strlen(buff)-1]='\0';

		//printf("Output of user command %s \n",buff);

		//alocate memory for 10 array of strings

		for(i = 0; i < 10; i++)

		{

			args[i] = (char*)malloc(20*sizeof(char));

		}

		//printf("%s\n",buff);

		//now make a argument list and add to string array

		p=strtok(buff," ");

		//printf("%s\n",p);

		strcpy(args[count++],p);

		while(p!=NULL)

		{

			p = strtok(NULL," ");

			if(p == NULL)

			break;

			//printf("in While %s\n",p);

			strcpy(args[count++],p);

		}

		//print args

		args[count]=NULL;

		//create child process

		pid = fork();

		if(pid == 0)

		{

			execvp(args[0],args);

		}

		else

		{

		//parent waits

		wait(0);

		}

	}

	return 0;

}