#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Fork the process
    pid_t pid = fork();

    if (pid < 0) {
        // Error in forking
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // Open the file in append mode so both processes can write to the file
    FILE *file = fopen("pid_file.txt", "a");

    if (file == NULL) {
        // Error in opening the file
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        pid_t child_pid = getpid();  // Get the child's PID
        fprintf(file, "Child Process PID: %d\n", child_pid);
        printf("Child Process: PID %d written to pid_file.txt\n", child_pid);
    } else {
        // Parent process
        pid_t parent_pid = getpid();  // Get the parent's PID
        fprintf(file, "Parent Process PID: %d\n", parent_pid);
        printf("Parent Process: PID %d written to pid_file.txt\n", parent_pid);
    }

    // Close the file
    fclose(file);

    return 0;
}
