#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

int main()
{
    char input[MAX];
    char result[MAX];
    char variable[MAX];

    int i = 0;
    int j = 0;

    printf("===== Double Quote Parser =====\n");
    printf("Enter text inside double quotes: ");

    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';

    /* Check opening and closing double quotes */
    if (input[0] != '"' ||
        input[strlen(input) - 1] != '"')
    {
        printf("Error: Input must be enclosed in double quotes.\n");
        return 1;
    }

    i = 1;

    while (input[i] != '\0' &&
           input[i] != '"' &&
           j < MAX - 1)
    {
        /* Variable expansion */
        if (input[i] == '$')
        {
            int k = 0;
            i++;

            while ((input[i] >= 'A' && input[i] <= 'Z') ||
                   (input[i] >= 'a' && input[i] <= 'z') ||
                   (input[i] >= '0' && input[i] <= '9') ||
                   input[i] == '_')
            {
                if (k < MAX - 1)
                    variable[k++] = input[i];

                i++;
            }

            variable[k] = '\0';

            char *value = getenv(variable);

            if (value != NULL)
            {
                for (int x = 0;
                     value[x] != '\0' && j < MAX - 1;
                     x++)
                {
                    result[j++] = value[x];
                }
            }
        }
        else
        {
            result[j++] = input[i++];
        }
    }

    result[j] = '\0';

    /* Validate closing quote */
    if (input[i] != '"')
    {
        printf("Error: Missing closing double quote.\n");
        return 1;
    }

    printf("\nOriginal Input : %s\n", input);
    printf("Parsed Content : %s\n", result);

    printf("\nDouble quotes preserve spaces.\n");
    printf("Variable expansion is allowed inside double quotes.\n");

    return 0;
}
