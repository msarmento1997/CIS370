#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 512
#define PERM 0644

int main(int argc, char* argv[])
{

	
	int fd1, fd2,outfile;
	char buf1[BUFFER],buf2[BUFFER];
	ssize_t nread1 , nread2;

	if(argc != 5)
	{
		printf("Error! Usage Mycat<s,e> file1 file2 file3\n");
	}

	if(argv[1][1] != 's' && argv[1][1] != 'e')
	{
		printf("Invalid argument use -s or -e\n");
	}

	//open file to read
	fd1 = open(argv[2],O_RDONLY);

	if(fd1 == -1)
	{
		printf("Error opening file1");
		return -1;
	}

	

	fd2 = open(argv[3], O_RDONLY);

	if(fd2 == -1)
	{
		printf("Error opening file2");
		close(fd1);
		return -2;
	}

	outfile = open(argv[4], O_WRONLY| O_CREAT| O_TRUNC, PERM);

	if(outfile == -1)
	{
		printf("Error opening file3");
		close(fd1);
		close(fd2);
		return -3;
	}


	if(argv[1][1] == 's')
	{
		while(nread1 = read(fd1,buf1, BUFFER))
		{
			if(write(outfile,buf1,nread1)<nread1)
			{
				printf("Error Writing to file.\n");
				close(fd1);
				close(outfile);
				return -3;
			}
		}
		while(nread2 = read(fd2,buf2, BUFFER))
		{
			if(write(outfile,buf2,nread2)<nread2)
			{
				printf("Error writing to file.\n");
				close(fd2);
				close(outfile);
				return -4;
			}
		}
		

	}

	if(argv[1][1] == 'e')
	{
		while(nread2 = read(fd2,buf2, BUFFER))
		{
			if(write(outfile,buf2,nread2)<nread2)
			{
				printf("Error writing to file.\n");
				close(fd2);
				close(outfile);
				return -4;
			}
		}

		while(nread1 = read(fd1,buf1, BUFFER))
		{
			if(write(outfile,buf1,nread1)<nread1)
			{
				printf("Error Writing to file.\n");
				close(fd1);
				close(outfile);
				return -3;
			}
		}

		

	}

	close(fd1);
	close(fd2);
	close(outfile);

	if(nread1 == -1)
		return -5;
	if(nread2 == -1)
		return -6;
	else
		return 0;






}