#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
char *pkt[2] = {
    "Hello there from CIS370",
    "Hope you have been enjoying the lab"};
int main(int argc, char *argv[])
{
    int pipeFD[2];
    int charCount;
    char buffer[32];
    pipe(pipeFD); /* set up pipe */
    if (fork() == 0)
    {
        close(pipeFD[1]); /*child reads (closes p[1])*/
        while((charCount = read(pipeFD[0],buffer, 8)) != 0)
        {
            buffer[charCount] = '\0'; /*string terminator*/
            printf("%d chars :\"%s\": received by child\n",charCount, buffer);
        }
        close(pipeFD[0]);
        exit(0); /*child done*/
    }
    close(pipeFD[0]); /*parent process*/
    wait(NULL);
    write(pipeFD[1], pkt[0], strlen(pkt[0]));
    write(pipeFD[1], pkt[1], strlen(pkt[1]));
    close(pipeFD[1]); /*finished writing p[1]*/
    //wait(NULL);
    return 1;
}