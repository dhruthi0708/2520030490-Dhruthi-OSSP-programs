#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 5
#define MAX_LENGTH 100

char history[MAX_HISTORY][MAX_LENGTH];
int count = 0;

/* Add command to history */
void add_command(char command[])
{
    if (count < MAX_HISTORY)
    {
        strcpy(history[count], command);
        count++;
    }
    else
    {
        /* Remove oldest command */
        for (int i = 1; i < MAX_HISTORY; i++)
        {
            strcpy(history[i - 1], history[i]);
        }

        strcpy(history[MAX_HISTORY - 1], command);
    }
}

/* Display history */
void display_history()
{
    printf("\n===== Command History =====\n");

    if (count == 0)
    {
        printf("History is empty.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

/* Retrieve a history entry */
void retrieve_command(int position)
{
    if (position < 1 || position > count)
    {
        printf("Invalid history position.\n");
        return;
    }

    printf("Retrieved Command: %s\n",
           history[position - 1]);
}

int main()
{
    char command[MAX_LENGTH];
    int position;

    printf("===== Command History System =====\n");
    printf("Maximum history size: %d\n", MAX_HISTORY);

    while (1)
    {
        printf("\nEnter command");
        printf(" (type 'history', 'get', or 'exit'): ");

        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0';

        /* Exit */
        if (strcmp(command, "exit") == 0)
        {
            break;
        }

        /* Display history */
        if (strcmp(command, "history") == 0)
        {
            display_history();
            continue;
        }

        /* Retrieve command */
        if (strcmp(command, "get") == 0)
        {
            printf("Enter history number: ");
            scanf("%d", &position);
            getchar();

            retrieve_command(position);
            continue;
        }

        /* Ignore empty commands */
        if (strlen(command) == 0)
        {
            printf("Empty command ignored.\n");
            continue;
        }

        /* Store command */
        add_command(command);

        printf("Command stored successfully.\n");
    }

    printf("\nHistory consistency check:\n");

    if (count <= MAX_HISTORY)
        printf("Valid: History is within capacity.\n");
    else
        printf("Invalid: History exceeds capacity.\n");

    printf("Program terminated.\n");

    return 0;
}
