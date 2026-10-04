#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    /* Create output file */
    fd = open("output.txt",
              O_WRONLY | O_CREAT | O_TRUNC,
              0644);

    if (fd == -1)
    {
        perror("output.txt");
        return 1;
    }

    /* Redirect stdout to file */
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return 1;
    }

    close(fd);

    printf("Hello from output redirection.\n");
    printf("This data is written into output.txt\n");

    return 0;
}
