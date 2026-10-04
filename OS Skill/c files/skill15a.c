#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    fd = open("combined.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("combined.txt");
        return 1;
    }

    /* Redirect stdout */
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 stdout");
        close(fd);
        return 1;
    }

    /* Redirect stderr to the same file descriptor */
    if (dup2(fd, STDERR_FILENO) == -1)
    {
        perror("dup2 stderr");
        close(fd);
        return 1;
    }

    close(fd);

    printf("Output: Program started.\n");
    fprintf(stderr, "Error: Test error message.\n");
    printf("Output: Program completed.\n");

    return 0;
}
