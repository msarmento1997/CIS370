#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_OF_ARGS 5
#define MAX_NUM_SIZE 256

int main(int argc, char *argv[])
{
	char argumentArray[MAX_NUM_OF_ARGS][MAX_NUM_SIZE];

	int i;
	
	for(i=0;i<MAX_NUM_OF_ARGS;i++)
	{
		//assign defaultArg to each element of the array
		strcpy(argumentArray[i],"defaultArg"); 
	}


	//check for the correct number of arguments
	if(argc>MAX_NUM_OF_ARGS)
	{
		printf("\nYour arguments exceeded the maximum of arguments(4)\n");
		return 1;	
	}
		

	for(i=0;i<argc;i++)
	{
		strcpy(argumentArray[i],argv[i]);
	}

	//display argument elements from the array
	for(i=0;i<MAX_NUM_OF_ARGS;i++)
	{
		printf("argumentArray[%d]: %s\n",i,argumentArray[i]);
	
	}	

}
