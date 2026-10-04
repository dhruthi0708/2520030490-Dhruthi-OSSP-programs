#include <stdio.h>
#include <signal.h>
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
        printf("Job started. PID = %d\n", getpid());

        raise(SIGSTOP);

        printf("Job resumed.\n");
        printf("Job completed successfully.\n");

        return 0;
    }

    waitpid(pid, &status, WUNTRACED);

    if (WIFSTOPPED(status))
    {
        printf("Job status: STOPPED\n");
        printf("Sending SIGCONT to resume the job...\n");

        kill(pid, SIGCONT);
    }

    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        printf("Job status: COMPLETED\n");
    }

    return 0;
}

