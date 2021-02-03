//main file

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "pid_man.c"



int main()
{
	int num;
	int user;
	int ret;
	int pid;
	int i;



	ret = allocate_map();
	//check if the pid map allocation failed
	if(ret == -1)
	{
		printf("Pid map allocation failed.\n");
		return 1;
	}


	//ask user to make a choice on allocating and deallocating pud and how they want to do it
	while(1)
	{
		printf("Press 1: Allocate single pid\n");
		printf("Press 2: Allocate all pid\n");
		printf("Press 3: Release single pid\n");
		printf("Press 4: Release all pid\n");
		printf("Press 5: Exit\n");

		scanf("%d",&user);

		//allocate a single pid
		if(user == 1)
		{
			ret = allocate_pid();

			if(ret == -1)
				printf("Pid allocation failed.\n");
			else
				printf("Pid allocated = %d\n", ret);
		}
		//allocate all pid
		if(user == 2)
		{
			

			for(i=0; i< MAX_PID- MIN_PID+1; i++)
			{	
				ret = allocate_pid();

			if(ret == -1)
				printf("Pid allocation failed.\n");
			else
				printf("Pid allocated = %d\n", ret);

			}

			/*if(ret == -1)
				printf("Pid allocation failed.\n");
			else
				printf("Pid allocated = %d\n", ret);*/
		}
		//deallocate a single pid
		if(user == 3)
		{
			printf("Enter the pid that you want to free.\n");
			scanf("%d",&pid);

			ret = release_pid(pid);

			if(ret == -1)
				printf("Invalid pid\n");
		}
		//deallocate all pid
		if(user == 4)
		{
			for(i=0;i< MAX_PID- MIN_PID; i++)
			{
				ret = release_pid(i);
			}

			if(ret == -1)
				printf("Invalid pid\n");
			else
				printf("All pid released\n");
		}
		//exit program
		if(user == 5)
		{
			printf("***Done***\n");
			exit(0);
		}

		else if(user<1 || user>5)
		{
			printf("Invalid choice\n");
		}

	}



}