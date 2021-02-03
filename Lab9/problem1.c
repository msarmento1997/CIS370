#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <time.h>

#define MAX_SIZE 8

typedef struct bufferStruct
{
	int in;
	int out;
	int content[MAX_SIZE];// will hold items produced (single int) 
} bufferStruct;



void printbuffer(struct bufferStruct *buffer);

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
	
	//Create our input buffer:
	char inBuffer[1];
	ssize_t nr1;

	//Initialize buffer (size of all variables plus size of itself 2ints, int array size of maxsize)
	struct bufferStruct *buffer = malloc(2 * sizeof(int) + MAX_SIZE * sizeof(int) + sizeof(struct bufferStruct));
	
	while(nr1 = read(0, inBuffer, 1)) //while we still are reading characters:
	{
		char cur; //Keeps current char of what to do from user	
		cur = inBuffer[0]; //Current character is first char of buffer
		
		
		if(cur == '0') //if exit char:
		{
			goto end;
		}
		else if(cur == 'p') //produce:
		{
			if((buffer->in + 1) % MAX_SIZE == buffer->out) //If the buffer is full:
			{
				write(1, "\t\t<Buffer Full!>\n", strlen("\t\t<Buffer Full!>\n"));
			}else{
				//If not full, produce next item between 1 and 40:
				int newitem = rand()%(40-1)+1;
				//Add it to the array:
				buffer->content[buffer->in] = newitem;
				buffer->in = (buffer->in + 1) % MAX_SIZE;
				printbuffer(buffer);
			}
		}
		else if(cur == 'c') //consume:
		{
			if(buffer->in==buffer->out) //if buffer is full:
			{
				write(1, "\t\t<Buffer Empty!>\n", strlen("\t\t<Buffer Empty!>\n"));
			}else{ //if not full:
				//Create our consumed index to consumed:
				int consumed = buffer->content[buffer->out];
				//Create a char array to print:
				char out[13] = "";
				//Copy consumed int to our string correct format:
				sprintf(out, "%d consumed\n", buffer->content[buffer->out]);
				buffer->out = (buffer->out + 1) % MAX_SIZE; //Increment our out pointer
				write(1, out, strlen(out)); //Write string to screen
				printbuffer(buffer);
			}
		}
	}
	
end:
	free(buffer); //free memory
	write(1, "Exiting...\n", strlen("Exiting...\n"));
	return 0;
}
