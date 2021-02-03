#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int num;
	int i;
	int j;
	pid_t cpid;
	int status;
	int result;
	int holder;

	if(argc >=2)
	{
		for(i=1; i<=3;i++)
		{
			result =0;
			
				if(i == 1)
				{
					if(fork() == 0)
					{
						for(j=1;j<argc;j++)
						{
							result += atoi(argv[j]);
						}
						printf("Child %d (pid:%d) Result: %d\n",i,getpid(),result);
						sleep(3);
						exit(i);
					}
				}
				
				if(i == 2)
				{
					result = 1;
					if(fork()==0)
					{
						for(j=1;j<argc;j++)
						{
							result *= atoi(argv[j]);
							//printf("result2 %d\n ", result);
						}
						printf("Child %d (pid:%d) Result: %d\n",i,getpid(),result);	
						sleep(3);
						exit(i);
					}
				}
				if(i == 3)
				{
					if(fork() == 0)
					{
						for(j=1;j<argc;j++)
						{
							holder = atoi(argv[j]);
							result += (holder * holder);
						}
						printf("Child %d (pid:%d) Result: %d\n",i,getpid(),result);
						sleep(3);
						exit(i);
					}
				}
				//sleep(5);
				//exit(i);
			
		}

		for(i =0; i<3; i++)
		{
			cpid = wait(&status);

		}
		printf("\nAll Children are done.\n");
	}
	else
	{
		printf("Argument list is empty.\n");
	}
	

}