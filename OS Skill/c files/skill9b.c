#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 200

void cmd_pwd()
{
    char path[MAX];

    if (getcwd(path, sizeof(path)) != NULL)
        printf("Current Directory: %s\n", path);
    else
        perror("pwd");
}

void cmd_cd(char *path)
{
    if (path == NULL)
    {
        printf("Usage: cd <directory>\n");
        return;
    }

    if (chdir(path) != 0)
        perror("cd");
    else
        printf("Directory changed successfully.\n");
}

void cmd_echo(char *text)
{
    if (text != NULL)
        printf("%s\n", text);
}

void cmd_help()
{
    printf("\n===== Built-in Commands =====\n");
    printf("cd <dir>     - Change directory\n");
    printf("pwd          - Show current directory\n");
    printf("echo <text>  - Display text\n");
    printf("help         - Show available commands\n");
    printf("exit         - Exit shell\n");
}

struct Builtin
{
    char *name;
    void (*function)();
};

int main()
{
    char input[MAX];
    char *command;
    char *argument;

    /* Dispatch table */
    struct Builtin builtins[] =
    {
        {"pwd", cmd_pwd},
        {"help", cmd_help}
    };

    int builtin_count = 2;

    printf("===== Built-in Command Shell =====\n");
    printf("Type 'help' for available commands.\n");

    while (1)
    {
        printf("\n$ ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        /* Ignore empty input */
        if (strlen(input) == 0)
            continue;

        command = strtok(input, " ");
        argument = strtok(NULL, "");

        /* Exit command */
        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        /* cd */
        if (strcmp(command, "cd") == 0)
        {
            cmd_cd(argument);
            continue;
        }

        /* echo */
        if (strcmp(command, "echo") == 0)
        {
            cmd_echo(argument);
            continue;
        }

        /* Search dispatch table */
        int found = 0;

        for (int i = 0; i < builtin_count; i++)
        {
            if (strcmp(command, builtins[i].name) == 0)
            {
                builtins[i].function();
                found = 1;
                break;
            }
        }

        /* Invalid command */
        if (!found)
        {
            printf("Invalid command: %s\n", command);
        }
    }

    return 0;
}
