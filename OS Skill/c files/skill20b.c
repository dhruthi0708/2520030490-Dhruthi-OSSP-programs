#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        /* Create a new process group */
        setpgid(0, 0);

        printf("Child process created.\n");
        printf("PID  = %d\n", getpid());
        printf("PGID = %d\n", getpgrp());

        sleep(3);

        printf("Child process completed.\n");

        return 0;
    }

    /* Assign child to its own process group */
    setpgid(pid, pid);

    printf("Parent/Shell process.\n");
    printf("Child PID  = %d\n", pid);
    printf("Child PGID = %d\n", getpgid(pid));

    printf("Sending signal to process group...\n");

    kill(-pid, SIGCONT);

    waitpid(pid, NULL, 0);

    printf("Child finished.\n");
    printf("Terminal control restored to shell.\n");

    return 0;
}
