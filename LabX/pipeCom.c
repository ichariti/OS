#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int fd[2];
	pid_t pid;
	char msg[]="I am your father";
	char buffer[100];
	
	//create a pipe
	if(pipe(fd)==-1){
		perror("pipe error");
		return 1;
	}
	//fork to create child
	pid=fork();
	if (pid<0){	//error in fork
		perror("fork failed");
		return 1;
	}
	else if (pid==0){ //child process
		close(fd[1]); //close the write end of the pipe
		read(fd[0], buffer, sizeof(buffer));
		printf("Child received: %s\n", buffer);
		close(fd[0]); //close the read end of pipe
	}
	else{ //parent process
		close(fd[0]); //close the read end of pipe
		write(fd[1], msg, strlen(msg)+1);
		close(fd[1]);
        wait(NULL); // Wait for the child to finish 
                //this is to avoid something called zombie processes
        }
	return 0;
} 
