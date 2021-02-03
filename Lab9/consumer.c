#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <time.h>
#include "buffer.h"



//Takes in a structure pointer, and then reads the contents based on the in and out indexes
void printbuffer(struct bufferStruct *buffer)
{
	int i;
	char out[3];

	//From i starting at the out index, while i is not the buffer in, 
	//we increment i and modulo it by max size to get next index.
	for(i = buffer->out%MAX_SIZE; i != buffer->in%MAX_SIZE; i=(i+1)%MAX_SIZE)
	{
		//copy int from array index i and a tab to char array out
		sprintf(out, "%d\t", buffer->content[i]);
		//Write out char array to screen
		write(1, out, strlen(out));
	}
	write(1, "\n", strlen("\n")); //newline spacing, done printing array
}


int main(void)
{
	srand(time(NULL)); //seed time for rand()

	//Variables for creating shared memory:
	int i, id;

	//Create our shared buffer structure:
	struct bufferStruct *buffer;

	//If couldn't create shared memory:
	if((id = shmget(key, MSIZ, IPC_CREAT | 0666)) < 0)
	{
		perror("Error creating shared memory!\n");
		return -1;
	}

	//If couldn't attach the memory to the program:
	if((buffer = (struct bufferStruct *)shmat(id, 0, 0)) <= (struct bufferStruct *)(0))
	{
		perror("Error attaching shared memory!\n");
		return -2;
	}
	
	//Create our input buffer:
	char inBuffer[1];
	ssize_t nr1;
	
	while(nr1 = read(0, inBuffer, 1)) //while we still are reading characters:
	{
		char cur; //Keeps current char of what to do from user	
		cur = inBuffer[0]; //Current character is first char of buffer
		
		
		if(cur == '0') //if exit char:
		{
			goto end;
		}
		else if(cur == '\n') //consume:
		{
			if(buffer->in==buffer->out) //if buffer is full:
			{
				write(1, "Buffer is empty...\n", strlen("Buffer is empty...\n"));
			}else{ //if not full:
				//Create our consumed index to consumed:
				int consumed = buffer->content[buffer->out];
				//Create a char array to print:
				char out[13] = "";
				//Copy consumed int to our string correct format:
				sprintf(out, "%d consumed\n", buffer->content[buffer->out]);
				buffer->out = (buffer->out + 1) % MAX_SIZE; //Increment our out pointer
				write(1, out, strlen(out)); //Write string to screen	
				printbuffer(buffer); //print our buffer contents array
			}
		}
	}
	
end:
	//Detatch buffer from program:
	if(shmdt(buffer) < 0)
	{
		write(1, "shmdt: shmdt failed!\n", strlen("shmdt: shmdt failed!\n"));
		return -1;
	}
	//Remove the shared memory:
	shmctl(id, IPC_RMID, NULL);
	write(1, "Exiting...\n", strlen("Exiting...\n"));
	return 0;
}
