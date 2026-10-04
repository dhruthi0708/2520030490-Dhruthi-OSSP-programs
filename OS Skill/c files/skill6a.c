#include <stdio.h>
#include <string.h>

#define MAX 200

int main()
{
    char input[MAX];
    char output[MAX];

    int i = 0;
    int j = 0;

    printf("===== Escape Sequence Parser =====\n");
    printf("Enter text with escape characters: ");

    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';

    while (input[i] != '\0' && j < MAX - 1)
    {
        if (input[i] == '\\')
        {
            i++;

            if (input[i] == '\0')
            {
                printf("\nError: Escape character at end.\n");
                return 1;
            }

            /* Handle escaped space */
            if (input[i] == ' ')
            {
                output[j++] = ' ';
            }

            /* Handle escaped special symbols */
            else if (input[i] == '\\' ||
                     input[i] == '|' ||
                     input[i] == '&' ||
                     input[i] == ';' ||
                     input[i] == '"' ||
                     input[i] == '\'')
            {
                output[j++] = input[i];
            }

            /* Handle newline */
            else if (input[i] == 'n')
            {
                output[j++] = '\n';
            }

            /* Handle tab */
            else if (input[i] == 't')
            {
                output[j++] = '\t';
            }

            /* Unknown escape */
            else
            {
                printf("\nWarning: Unknown escape \\%c\n",
                       input[i]);

                output[j++] = input[i];
            }
        }
        else
        {
            output[j++] = input[i];
        }

        i++;
    }

    output[j] = '\0';

    printf("\nOriginal Input:\n%s\n", input);

    printf("\nParsed Output:\n%s\n", output);

    printf("\nEscape sequence processing completed.\n");

    return 0;
}
