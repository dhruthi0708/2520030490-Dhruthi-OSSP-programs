#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    char command[100];
    char *path;
    char *path_copy;
    char *directory;

    printf("===== Command Path Resolver =====\n");

    printf("Enter command name: ");
    scanf("%99s", command);

    /* Get PATH variable */
    path = getenv("PATH");

    if (path == NULL)
    {
        printf("PATH variable not found.\n");
        return 1;
    }

    /* Create copy of PATH */
    path_copy = malloc(strlen(path) + 1);

    if (path_copy == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    strcpy(path_copy, path);

    /* Split PATH into directories */
    directory = strtok(path_copy, ":");

    while (directory != NULL)
    {
        char full_path[PATH_MAX];

        snprintf(full_path,
                 sizeof(full_path),
                 "%s/%s",
                 directory,
                 command);

        /* Check executable permission */
        if (access(full_path, X_OK) == 0)
        {
            printf("\nCommand found!\n");
            printf("Executable: %s\n", full_path);

            free(path_copy);
            return 0;
        }

        directory = strtok(NULL, ":");
    }

    printf("\nCommand not found: %s\n", command);

    free(path_copy);

    return 1;
}
