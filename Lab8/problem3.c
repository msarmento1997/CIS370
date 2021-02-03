#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

//defining the buffer size
#define SIZE_OF_BUFFER 256

int main( int argc, char* argv[] ) {
  
	int fpipe[2];
	pid_t child_id;
	//buffer to read the input file
	char readBuffer[SIZE_OF_BUFFER];

	//creating a pipe
	pipe(fpipe);
	  
	//checking for valid number of parameters entered
	if( argc != 3 ) {
		printf("ERROR: Enter 2 parameters only.\n");
		exit(1);
	}
	//Source file received as argument 1
	int sourceFile = open(argv[1], 0);

	//Destination file received as argument 2,if file does not exist it will create one

	int destinationFile = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);

		 ssize_t nbytes;

	//check if file is able to open or not
	if (sourceFile == -1 || destinationFile == -1) {
		printf("ERROR: Couldnt open file\n");
		exit(1);
	}
	//fork the child
	child_id = fork();

	if (child_id == 0) {
		// inside the child prcocess
		close(fpipe[1]);

		while (nbytes =read(fpipe[0], readBuffer, sizeof(readBuffer))) {
			// Writing to the destination file from pipe
			write(destinationFile, readBuffer, nbytes);
		}

		close(fpipe[0]);
		close(destinationFile);
	}
	else {
		// inside the parent process
		close(fpipe[0]);

		// code to read from a text file and store in pipe
		while (nbytes=read(sourceFile, readBuffer, sizeof(readBuffer))) {
			write(fpipe[1], readBuffer, nbytes);
			memset(readBuffer, 0, nbytes);
		}

		close(fpipe[1]);
		close(sourceFile);
		wait(NULL);
	}
}