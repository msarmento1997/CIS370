#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_OF_ARGS 5

int main(int argc, char *argv[])
{

	char **argumentArray = NULL;
	
	argumentArray = (char**) malloc((argc+1)*sizeof(char*));
	
	
	int i;
	
	for(i=0;i<argc;i++)
	{
		argumentArray[i]= (char*)malloc((strlen(argv[i])+1)*sizeof(char));
		strcpy(argumentArray[i],argv[i]);
	}
	
	//display argument elements from the array
	for(i=0;i<argc;i++)
	{
		printf("argumentArray[%d]: %s\n",i,argumentArray[i]);
	
	}

	//freeing memory
	for(i=0;i<argc;i++)
	{
		free(argumentArray[i]);
	}
	free(argumentArray);
	
	return 0;
}	

