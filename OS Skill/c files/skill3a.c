#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 10
#define MAX_LENGTH 100

char history[MAX_HISTORY][MAX_LENGTH];
int history_count = 0;
int current = -1;

void add_history(char *cmd)
{
    if (strlen(cmd) == 0)
        return;

    if (history_count < MAX_HISTORY)
    {
        strcpy(history[history_count], cmd);
        history_count++;
    }
    else
    {
        for (int i = 1; i < MAX_HISTORY; i++)
            strcpy(history[i - 1], history[i]);

        strcpy(history[MAX_HISTORY - 1], cmd);
    }

    current = history_count;
}

void show_history()
{
    printf("\nCommand History:\n");

    for (int i = 0; i < history_count; i++)
        printf("%d: %s\n", i + 1, history[i]);
}

void previous_command()
{
    if (history_count == 0)
    {
        printf("No previous command.\n");
        return;
    }

    if (current > 0)
        current--;

    printf("Previous Command: %s\n", history[current]);
}

void next_command()
{
    if (history_count == 0)
    {
        printf("No next command.\n");
        return;
    }

    if (current < history_count - 1)
    {
        current++;
        printf("Next Command: %s\n", history[current]);
    }
    else
    {
        current = history_count;
        printf("Next Command: Empty\n");
    }
}

int main()
{
    char command[MAX_LENGTH];

    printf("===== Command History System =====\n");
    printf("Type commands to store them.\n");
    printf("history - Show history\n");
    printf("prev    - Previous command\n");
    printf("next    - Next command\n");
    printf("exit    - Exit\n");

    while (1)
    {
        printf("\n$ ");

        if (fgets(command, MAX_LENGTH, stdin) == NULL)
            break;

        /* Remove newline */
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        if (strcmp(command, "history") == 0)
        {
            show_history();
        }
        else if (strcmp(command, "prev") == 0)
        {
            previous_command();
        }
        else if (strcmp(command, "next") == 0)
        {
            next_command();
        }
        else
        {
            add_history(command);
            printf("Command stored: %s\n", command);
        }
    }

    return 0;
}
