#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 200

int valid_name(char *name)
{
    if (name == NULL || name[0] == '\0')
        return 0;

    /* First character must be letter or underscore */
    if (!isalpha(name[0]) && name[0] != '_')
        return 0;

    /* Remaining characters */
    for (int i = 1; name[i] != '\0'; i++)
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return 0;
    }

    return 1;
}

int main()
{
    char input[MAX];
    char variable[MAX];
    char value[MAX];

    printf("===== Export Command Parser =====\n");

    printf("Enter export command:\n");
    printf("Example: export NAME=Dhruthi\n\n");

    printf("$ ");

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    /* Check export keyword */
    if (strncmp(input, "export ", 7) != 0)
    {
        printf("Error: Invalid export syntax.\n");
        return 1;
    }

    char *assignment = input + 7;

    /* Find '=' */
    char *equal = strchr(assignment, '=');

    if (equal == NULL)
    {
        printf("Error: Missing '='.\n");
        return 1;
    }

    /* Extract variable name */
    int name_length = equal - assignment;

    if (name_length <= 0 ||
        name_length >= MAX)
    {
        printf("Error: Invalid variable name.\n");
        return 1;
    }

    strncpy(variable, assignment, name_length);
    variable[name_length] = '\0';

    /* Extract value */
    strcpy(value, equal + 1);

    /* Validate variable name */
    if (!valid_name(variable))
    {
        printf("Error: Invalid variable name: %s\n",
               variable);
        return 1;
    }

    printf("\nVariable Name: %s\n", variable);
    printf("Variable Value: %s\n", value);

    /* Check existing variable */
    char *old_value = getenv(variable);

    if (old_value != NULL)
    {
        printf("Existing Value: %s\n", old_value);
        printf("Updating existing variable...\n");
    }
    else
    {
        printf("Variable does not exist.\n");
        printf("Creating new variable...\n");
    }

    /* Update environment variable */
    if (setenv(variable, value, 1) != 0)
    {
        perror("setenv");
        return 1;
    }

    printf("Environment variable updated successfully.\n");

    /* Display new value */
    printf("New Value: %s\n", getenv(variable));

    /* Create child process */
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        /* Child process */
        printf("\nChild Process:\n");
        printf("%s=%s\n", variable, getenv(variable));

        exit(0);
    }
    else
    {
        /* Parent process */
        waitpid(pid, NULL, 0);

        printf("\nParent Process:\n");
        printf("Child process completed.\n");
    }

    return 0;
}
