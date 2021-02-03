#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define BUFFER 1024
int main(int argc, char **argv)
{
	int fd1;
	int i,j, k=0;
	char buf1[BUFFER];
	char buf2[BUFFER];
	ssize_t nread;

	if(argc !=2)
	{
		//error invalid arguments
		perror("Invalid argument Count");
		return -1;
	}

	if(argc == 2)
	{
		//open file to read from
		fd1 = open(argv[1],O_RDONLY);

		//error opening file
		if(fd1 == -1)
		{
			//error opening file
			perror("Error opening file");
			close(fd1);
			return -1;
		}

		while(nread = read(fd1, buf1, BUFFER) )
		{
			if(nread == -1)
			{
				//error reading from file
				perror("Error reading from file");
				close(fd1);
				return -1;
			}

			//iterate over array buf1 
			for(i=0;i<=nread-1;i++)
			{
				//if buf1[i] contains a newline
				if(buf1[i] == '\n')
				{
					//reverse file character by character until newline
					for(j=k;i>=k;j++,i--)
					{
						buf2[j]=buf1[i];
						//printf("%c", buf2[j]);
					}
					k=j;//k becomes a holder for the buf2 array so no data is overwritten
				}
			
			}


			//check if error writing to stdout
			if(write(1, buf2, nread) == -1)
				perror("Error writing to STDOUT");
			//printf is used just to print a newline for cleaner results in CLI
			printf("\n");
		}
	}
	return 0;

	//close file
	close(fd1);

}