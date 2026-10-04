#include <stdio.h>
#include <stdlib.h>
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
        printf("Background job started. PID = %d\n", getpid());

        sleep(5);

        printf("Background job completed. PID = %d\n", getpid());
        exit(0);
    }

    printf("Parent: Background job launched. PID = %d\n", pid);
    printf("Parent: Prompt is available immediately.\n");

    /* Non-blocking check */
    waitpid(pid, &status, WNOHANG);

    printf("Parent continues working...\n");

    sleep(6);

    /* Check the completed process */
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        printf("Background job finished successfully.\n");
    }

    return 0;
}
