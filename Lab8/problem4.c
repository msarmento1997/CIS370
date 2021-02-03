#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER 128



int main(int argc, char **argv)
{
	if(argc != 2) //Wrong number of arguments
	{
		printf("[error] ./P4 <filename>\n");

		return(-1);
	}
	
	//File output descriptor (argv[1]):
	int fdout = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC,0644); 
	if(fdout == -1) {
		printf("Error opening file.\n");

		return(-2);
	}
	
	//Create our output buffer:
	char outBuffer[BUFFER] = "Index of %0";
	char inBuffer[BUFFER];
	int i = 0; //variable to hold current index
	ssize_t nr1;
	
	while(nr1 = read(0, inBuffer, BUFFER)) //while we still are reading characters:
	{
		char c; //Keeps current char of what to do from user
		
		int outputchoice = 1; //Define output as 1 to start
		
		c = inBuffer[0]; //Current character is first char of buffer
		
		if(c == '0') //if exit char:
		{
			break; //break loop
		}
		else if(c == 'f') //if going to file
		{
			if(outputchoice == 1) //and is using screen:
			{
				outputchoice = dup2(fdout,1); //change stdio to file descriptor
			}
		}
		else if(c == 's') //if printing to the screen:
		{
			outputchoice = dup2(0,1); //change stdout to 
		}
		
		sprintf(outBuffer, "Index of %d\n", ++i); //Increment i, copy string to outbuffer

		write(1, outBuffer, strlen(outBuffer)); //where char outbuffer[128]; 
	}

	close(fdout); //close our file descriptor
	
	return 0;
}
