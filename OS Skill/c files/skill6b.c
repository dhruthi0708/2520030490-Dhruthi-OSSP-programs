#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    printf("===== Process Execution =====\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    /* Child process */
    if (pid == 0)
    {
        printf("\nChild Process Created\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("\nExecuting ls command...\n");

        execlp("ls", "ls", "-l", NULL);

        /* Executes only if execlp fails */
        perror("Execution failed");

        exit(1);
    }

    /* Parent process */
    else
    {
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("\nWaiting for child process...\n");

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("\nChild exited with status: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("\nChild terminated abnormally.\n");
        }

        printf("Parent process completed.\n");
    }

    return 0;
}
