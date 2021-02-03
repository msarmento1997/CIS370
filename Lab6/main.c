#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

int ForkExec(char *program, char* args)
{
pid_t pid;
pid = fork();
if(pid < 0){
    printf("Fork failed\n");
}else if(pid == 0){
    execlp(program, program, args, NULL);
}
return pid;
}

int main(int argc, char *argv[])
{
int temp;

for(int i = 1; i < argc; i++){
    if(i + 1 < argc){
      if(strcmp(argv[i + 1], ":") == 0){
        temp = ForkExec(argv[i], NULL);
        wait(NULL);
        printf("\nForkExec returned %d\n",temp);
        i++;
      }else{
        temp = ForkExec(argv[i], argv[i + 1]);
        wait(NULL);
        printf("\nForkExec returned %d\n",temp);
        i = i + 2;
      }
    }
}

return 0;
}
