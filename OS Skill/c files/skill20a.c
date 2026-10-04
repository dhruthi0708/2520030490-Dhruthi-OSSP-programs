#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t child_pid;

void handle_sigtstp(int sig)
{
    printf("\nSIGTSTP received.\n");
    
    if (child_pid > 0)
    {
        kill(child_pid, SIGSTOP);
        printf("Foreground job suspended.\n");
    }
}

int main()
{
    int status;

    child_pid = fork();

    if (child_pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0)
    {
        signal(SIGTSTP, SIG_DFL);

        printf("Foreground job started. PID = %d\n", getpid());
        printf("Job is running...\n");

        sleep(10);

        printf("Job completed.\n");
        return 0;
    }

    signal(SIGTSTP, handle_sigtstp);

    printf("Shell monitoring job PID = %d\n", child_pid);

    sleep(2);

    /* Simulate Ctrl+Z */
    kill(getpid(), SIGTSTP);

    waitpid(child_pid, &status, WUNTRACED);

    if (WIFSTOPPED(status))
    {
        printf("Job state: STOPPED\n");
        printf("Sending SIGCONT...\n");

        kill(child_pid, SIGCONT);
    }

    waitpid(child_pid, &status, 0);

    if (WIFEXITED(status))
    {
        printf("Job state: COMPLETED\n");
    }

    return 0;
}
