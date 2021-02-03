#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "Pid_Manager.h"

/*create and initializes a data structure for representing pids*/
int allocate_map(void)
{
	
	pid_map = (char*)malloc((MAX_PID- MIN_PID + 1) * sizeof(char));

	if(pid_map == NULL)
		return -1; //if unsuccessful
	memset((void *)pid_map, NULL, MAX_PID - MIN_PID+1);
	return 1; //successful
}
//allocate pid
int allocate_pid(void)
{
	int i;

	for(i=0; i<=MAX_PID -MIN_PID; i++)
	{
		//check for the first free slot
		if(pid_map[i] == 0)
		{
			pid_map[i] = 1;

			return MIN_PID + i; //Successful, returning pid
		}
	}

	return -1; //Unsucessful

}
//deallocate pid
int release_pid(int pid)
{
	//checks if the pid is within MIN_PID and MAX_PID and if it has been allocated or not
	if((pid >= MIN_PID) && (pid <= MAX_PID) && (pid_map[pid - MIN_PID] == 1))
	{
		pid_map[pid - MIN_PID] = 0;

		return 1; //successful
	}
	else
	{
		return -1; //unsuccessful
	}
}