#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid1,pid2,pid3;
	
	pid1=fork();
	if (pid1<0){	//error in fork
		perror("fork 1 failed");
		exit(EXIT_FAILURE);
	}
	else if (pid1==0){ //child 1 process
		printf("Child 1 Process: PID=%d, Parent PID=%d\n", getpid(),getppid());
		exit(0);  // Child process exits
	}
	else{ //parent process
		//printf("Parent Process: PID=%d, Created Child 1 PID=%d\n", getpid(),pid1);
		pid2 = fork();
		if (pid2<0){	//error in fork
			perror("fork 2 failed");
			exit(EXIT_FAILURE);
		}
		else if (pid2 == 0) {
            // Child process of the second fork
            printf("Child 2: Process ID = %d, Parent ID = %d\n", getpid(), getppid());
            exit(0);  // Child process exits
        } else {
            // Parent process after second fork
            // Third fork
            pid3 = fork();
            if (pid3<0){	//error in fork
				perror("fork 3 failed");
				exit(EXIT_FAILURE);
			}else if (pid3 == 0) {
                // Child process of the third fork
                printf("Child 3: Process ID = %d, Parent ID = %d\n", getpid(), getppid());
                exit(0);  // Child process exits
            } else {
                // Parent process after third fork
                printf("Parent: Process ID = %d\n", getpid());
                 // Parent waits for all child processes to finish
                wait(NULL); // Wait for the first child (pid1)
                wait(NULL); // Wait for the second child (pid2)
                wait(NULL); // Wait for the third child (pid3)
                //this is to avoid something called zombie processes
            }
		}	
	}
	return 0;
}
