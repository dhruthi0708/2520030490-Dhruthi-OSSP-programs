#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    printf("===== Process Synchronization =====\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        /* Child process */
        printf("\nChild Process Started\n");
        printf("Child PID: %d\n", getpid());

        sleep(3);

        printf("Child Process Completed\n");

        exit(0);
    }
    else
    {
        /* Parent process */
        printf("\nParent Process Started\n");
        printf("Parent PID: %d\n", getpid());
        printf("Monitoring Child PID: %d\n", pid);

        printf("Parent waiting for child...\n");

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("\nChild terminated normally.\n");
            printf("Child Exit Status: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("\nChild terminated abnormally.\n");
        }

        printf("Parent Process Completed\n");
    }

    return 0;
}
