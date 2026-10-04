#include <stdio.h>
#include <string.h>

int parse_command(const char *command)
{
    if (command == NULL || strlen(command) == 0)
    {
        return 0;
    }

    return 1;
}

int execute_command(const char *command)
{
    if (!parse_command(command))
    {
        return 0;
    }

    printf("Executing command: %s\n", command);

    return 1;
}

int main()
{
    const char *commands[] =
    {
        "echo Hello",
        "pwd",
        ""
    };

    int i;

    for (i = 0; i < 3; i++)
    {
        if (execute_command(commands[i]))
        {
            printf("Interface validation: PASS\n");
        }
        else
        {
            printf("Interface validation: FAIL\n");
        }
    }

    printf("End-to-end module test completed.\n");

    return 0;
}
