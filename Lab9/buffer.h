#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_SIZE 8

typedef struct bufferStruct
{
	int in;
	int out;
	int content[MAX_SIZE];// will hold items produced (single int) 
} bufferStruct;

key_t key = 1967;
#define MSIZ sizeof(struct bufferStruct)