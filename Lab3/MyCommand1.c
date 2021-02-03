#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	int argcIndex;
	int envpIndex;
	for(argcIndex = 0; argcIndex <argc; argcIndex++)
	{
		printf("argc[%d]: %s\n",argcIndex,argv[argcIndex]);
	}
	
	


}
