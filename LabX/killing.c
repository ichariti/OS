#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handle_sigterm(int sig) {
    printf("Child process received SIGTERM, cleaning up...\n");
    exit(0);  // Exit gracefully
}

int main() {
    pid_t pid;

    pid = fork();  // Create a child process

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: Set up signal handler
        signal(SIGTERM, handle_sigterm);  // Register the handler for SIGTERM
        printf("Child process running with PID: %d\n", getpid());
        while (1) {
            // The child is now running and will handle SIGTERM
            sleep(1);  // Simulating work
        }
    } else {
        // Parent process: Send a signal to the child
        printf("Parent process with PID: %d sending SIGTERM to child PID: %d\n", getpid(), pid);
        sleep(2);  // Give the child some time to run

        // Send SIGTERM signal to the child process
        if (kill(pid, SIGTERM) == 0) {
            printf("SIGTERM sent to child process %d\n", pid);
        } else {
            perror("kill failed");
        }

        // Wait for the child to terminate
        wait(NULL);
    }

    return 0;
}
