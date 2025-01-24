#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent process started. PID: %d\n", getpid());

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process created. PID: %d\n", getpid());
        printf("Child process terminating to become a zombie.\n");
        exit(0); // Child exits, becoming a zombie
    } else {
        // Parent process
        printf("Parent process continuing. PID: %d\n", getpid());
        printf("Child process PID: %d should now be a zombie.\n", pid);

        // Sleep to allow observation of the zombie process
        sleep(10);

        // Collect the child process (remove zombie state)
        wait(NULL);
        printf("Child process (PID: %d) collected, no longer a zombie.\n", pid);
    }

    return 0;
}
