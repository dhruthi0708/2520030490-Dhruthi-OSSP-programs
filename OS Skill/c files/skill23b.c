#include <stdio.h>
#include <unistd.h>
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
        printf("Child: executing command.\n");

        execlp("echo",
               "echo",
               "Syscall path: fork -> exec -> exit",
               NULL);

        perror("exec");
        return 1;
    }

    printf("Parent: fork created child PID = %d\n", pid);

    waitpid(pid, NULL, 0);

    printf("Parent: wait completed.\n");
    printf("Execution path finished successfully.\n");

    return 0;
}
