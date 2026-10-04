#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 100

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
}

void cmd_echo(char *text)
{
    if (text != NULL)
        printf("%s\n", text);
}

void cmd_help()
{
    printf("\nBuilt-in Commands:\n");
    printf("cd <dir>  - Change directory\n");
    printf("pwd       - Show current directory\n");
    printf("echo <text> - Display text\n");
    printf("help      - Show available commands\n");
    printf("exit      - Exit program\n");
}

int main()
{
    char input[MAX];
    char *command;
    char *argument;

    /* Dispatch table */
    struct Builtin
    {
        char *name;
        void (*function)();
    };

    struct Builtin builtins[] =
    {
        {"pwd", cmd_pwd},
        {"help", cmd_help},
        {NULL, NULL}
    };

    int builtin_count = 2;

    printf("===== Built-in Command Shell =====\n");
    printf("Type 'help' to see commands.\n");

    while (1)
    {
        printf("\n$ ");

        if (fgets(input, MAX, stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        command = strtok(input, " ");
        argument = strtok(NULL, "");

        if (command == NULL)
        {
            continue;
        }

        /* Exit */
        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        /* cd needs an argument */
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

        if (!found)
        {
            printf("Invalid command: %s\n", command);
        }
    }

    return 0;
}
