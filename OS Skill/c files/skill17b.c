#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Foreground job started.\n");
        printf("PID: %d\n", getpid());

        sleep(3);

        printf("Foreground job completed.\n");

        return 0;
    }

    printf("Shell: Target job identified.\n");
    printf("Shell: Transferring control to PID %d\n", pid);

    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        printf("Shell: Job completed successfully.\n");
        printf("Shell: Foreground control restored.\n");
    }

    return 0;
}
