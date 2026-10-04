#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t foreground_pid;

void handle_sigint(int sig)
{
    if (foreground_pid > 0)
    {
        printf("\nShell: SIGINT received.\n");
        printf("Shell: Forwarding SIGINT to foreground job.\n");

        kill(foreground_pid, SIGINT);
    }
}

int main()
{
    int status;

    foreground_pid = fork();

    if (foreground_pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (foreground_pid == 0)
    {
        signal(SIGINT, SIG_DFL);

        printf("Foreground job started. PID = %d\n", getpid());

        sleep(10);

        printf("Foreground job completed.\n");

        return 0;
    }

    signal(SIGINT, handle_sigint);

    printf("Shell started.\n");
    printf("Foreground job PID = %d\n", foreground_pid);

    sleep(2);

    printf("Sending SIGINT to foreground job...\n");

    kill(getpid(), SIGINT);

    waitpid(foreground_pid, &status, 0);

    if (WIFSIGNALED(status))
    {
        printf("Foreground job terminated by signal.\n");
    }

    printf("Shell continues running.\n");

    return 0;
}
