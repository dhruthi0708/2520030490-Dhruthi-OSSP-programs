#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_LENGTH 100

struct Pipeline
{
    char commands[MAX_COMMANDS][MAX_LENGTH];
    int count;
};

/* Add command to pipeline */
void add_command(struct Pipeline *pipeline, char command[])
{
    if (pipeline->count >= MAX_COMMANDS)
    {
        printf("Pipeline capacity exceeded.\n");
        return;
    }

    strcpy(pipeline->commands[pipeline->count],
           command);

    pipeline->count++;
}

/* Display pipeline */
void display_pipeline(struct Pipeline *pipeline)
{
    printf("\n===== Pipeline Structure =====\n");

    for (int i = 0; i < pipeline->count; i++)
    {
        printf("[%d] %s", i + 1,
               pipeline->commands[i]);

        if (i < pipeline->count - 1)
            printf(" -> ");

        printf("\n");
    }
}

/* Validate pipeline */
int validate_pipeline(struct Pipeline *pipeline)
{
    if (pipeline->count == 0)
    {
        printf("Error: Empty pipeline.\n");
        return 0;
    }

    if (pipeline->count > MAX_COMMANDS)
    {
        printf("Error: Too many commands.\n");
        return 0;
    }

    for (int i = 0; i < pipeline->count; i++)
    {
        if (strlen(pipeline->commands[i]) == 0)
        {
            printf("Error: Empty command at position %d.\n",
                   i + 1);
            return 0;
        }
    }

    return 1;
}

int main()
{
    struct Pipeline pipeline;
    pipeline.count = 0;

    char input[MAX_LENGTH];

    printf("===== Pipeline Structure =====\n");

    printf("Enter commands one by one.\n");
    printf("Type 'done' when finished.\n\n");

    while (pipeline.count < MAX_COMMANDS)
    {
        printf("Command %d: ",
               pipeline.count + 1);

        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "done") == 0)
            break;

        if (strlen(input) == 0)
        {
            printf("Empty command not allowed.\n");
            continue;
        }

        add_command(&pipeline, input);
    }

    /* Validate pipeline */
    if (!validate_pipeline(&pipeline))
    {
        printf("Invalid pipeline configuration.\n");
        return 1;
    }

    display_pipeline(&pipeline);

    printf("\nPipeline contains %d commands.\n",
           pipeline.count);

    printf("Execution order:\n");

    for (int i = 0; i < pipeline.count; i++)
    {
        printf("%d. %s\n",
               i + 1,
               pipeline.commands[i]);
    }

    /*
       Demonstrate process creation
       for each pipeline command.
    */

    printf("\nCreating processes...\n");

    for (int i = 0; i < pipeline.count; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            return 1;
        }

        if (pid == 0)
        {
            printf("Child process %d created for: %s\n",
                   getpid(),
                   pipeline.commands[i]);

            exit(0);
        }
    }

    /* Parent waits for all children */
    for (int i = 0; i < pipeline.count; i++)
    {
        wait(NULL);
    }

    printf("\nAll pipeline processes completed.\n");

    return 0;
}
