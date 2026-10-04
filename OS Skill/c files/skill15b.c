#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    /* First command: echo data into pipe */
    p1 = fork();

    if (p1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp("echo", "echo", "Hello Linux Pipeline", NULL);

        perror("echo");
        exit(1);
    }

    /* Second command: read from pipe and redirect to file */
    p2 = fork();

    if (p2 == 0)
    {
        FILE *file = fopen("pipeline.txt", "w");

        if (file == NULL)
        {
            perror("pipeline.txt");
            exit(1);
        }

        dup2(pipefd[0], STDIN_FILENO);
        dup2(fileno(file), STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execlp("cat", "cat", NULL);

        perror("cat");
        fclose(file);
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    printf("Pipeline execution completed.\n");
    printf("Output saved in pipeline.txt\n");

    return 0;
}
