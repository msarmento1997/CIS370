#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 512
#define PERM 0644

int main(int argc, char ** argv)
{
	int fd1,outfile;
	char buf1[BUFFER],buf2[BUFFER];
	ssize_t nread;
	int i;
	int j;

	if(argc<2 || argc>4)
	{
		printf("Error! Invalid arguments.\n");
		return -1;
	}

	//if two arguments were made
	if(argc ==2)
	{
		fd1 = open(argv[1],O_RDONLY);
		if(fd1 == -1)
		{
			printf("Error opening file1\n");
			return -2;
		}

		while(nread = read(fd1, buf1,BUFFER))
		{
			/*
			*
			* nread is the total char/bytes read
			* An array starts at index 0
			* If I were to read 15 char and put those in nread,
			* what is my the final index that hold the last 15th char? 
			* Is it nread[15] or nread[14]?	
			*
			*/
			if(nread == -1)
				printf("Error reading file.\n");
			for(i=nread-1, j=0; i>=0;i--,j++) // <<<< i = nread will give you some empty/garbage value since there is
							  // nothing on buf1[nread], you want buf1[nread-1]
			{
				buf2[j]=buf1[i];
				//printf("%c",buf2[j]);
			}

			write(1,buf2,nread+1);

		}
		
	}


	//if 4 arguments were made
	if(argc==4)
	{

		if(argv[1][1] != 'f')
		{
			printf("Error! Invalid argument use -f\n");
		}

		fd1 = open(argv[2],O_RDONLY);
		if(fd1 == -1)
		{
			printf("Error opening file1\n");
			return -2;
		}
		outfile = open(argv[3],O_WRONLY|O_CREAT|O_TRUNC, PERM);

		if(outfile == -1)
		{
			printf("Error opening output file\n");
			close(fd1);

		}

		while(nread = read(fd1, buf1,BUFFER))
		{
			/*
			*	
			*	Same mistake over here!		
			*
			*/
			if(nread == -1)
				printf("Error reading file.\n");
			for(i=nread-1, j=0; i>=0;i--,j++)
			{
				buf2[j]=buf1[i];
				//printf("%c",buf2[j]);
			}

			write(outfile,buf2,nread);

		}


	}
	close(fd1);
	
	close(outfile);

}