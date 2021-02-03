#define DataSize 32 

typedef struct SharedMem
{
	int In;
	int Out;
	char Data[DataSize];
}SharedMem;

#define SharedMemSize sizeof(SharedMem)

