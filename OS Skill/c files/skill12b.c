#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipe1[2];
    int pipe2[2];

    pid_t pid1, pid2, pid3;

    /* Create first pipe */
    if (pipe(pipe1) == -1)
    {
        perror("pipe1");
        return 1;
    }

    /* Create second pipe */
    if (pipe(pipe2) == -1)
    {
        perror("pipe2");
        return 1;
    }

    printf("===== Multiple Pipe Pipeline =====\n");
    printf("Pipeline:\n");
    printf("ls -l | grep \"^-\" | wc -l\n\n");

    /* First process */
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid1 == 0)
    {
        /* ls -l */

        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);

        /* stdout -> pipe1 */
        dup2(pipe1[1], STDOUT_FILENO);

        close(pipe1[1]);

        execlp("ls", "ls", "-l", NULL);

        perror("execlp ls");
        exit(1);
    }

    /* Second process */
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid2 == 0)
    {
        /* grep "^-"
           stdin <- pipe1
           stdout -> pipe2
        */

        close(pipe1[1]);
        close(pipe2[0]);

        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe2[1]);

        execlp("grep", "grep", "^-", NULL);

        perror("execlp grep");
        exit(1);
    }

    /* Third process */
    pid3 = fork();

    if (pid3 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid3 == 0)
    {
        /* wc -l */

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);

        /* stdin <- pipe2 */
        dup2(pipe2[0], STDIN_FILENO);

        close(pipe2[0]);

        execlp("wc", "wc", "-l", NULL);

        perror("execlp wc");
        exit(1);
    }

    /* Parent closes all pipe descriptors */
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    /* Wait for all processes */
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("All pipeline processes completed.\n");

    return 0;
}
