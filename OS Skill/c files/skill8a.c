#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

void expand_variables(char *input, char *output)
{
    int i = 0;
    int j = 0;

    while (input[i] != '\0' && j < MAX - 1)
    {
        if (input[i] == '$')
        {
            char variable[100];
            int k = 0;

            i++;

            /* Handle ${VARIABLE} */
            if (input[i] == '{')
            {
                i++;

                while (input[i] != '\0' &&
                       input[i] != '}' &&
                       k < 99)
                {
                    variable[k++] = input[i++];
                }

                variable[k] = '\0';

                if (input[i] == '}')
                    i++;
            }
            /* Handle $VARIABLE */
            else
            {
                while (input[i] != '\0' &&
                       (isalnum(input[i]) || input[i] == '_') &&
                       k < 99)
                {
                    variable[k++] = input[i++];
                }

                variable[k] = '\0';
            }

            if (k > 0)
            {
                char *value = getenv(variable);

                if (value != NULL)
                {
                    for (int x = 0;
                         value[x] != '\0' && j < MAX - 1;
                         x++)
                    {
                        output[j++] = value[x];
                    }
                }
                else
                {
                    printf("Undefined variable: %s\n", variable);
                }
            }
            else
            {
                output[j++] = '$';
            }
        }
        else
        {
            output[j++] = input[i++];
        }
    }

    output[j] = '\0';
}

int main()
{
    char input[MAX];
    char output[MAX];

    printf("===== Variable Expansion =====\n");

    printf("Enter text: ");
    fgets(input, MAX, stdin);

    input[strcspn(input, "\n")] = '\0';

    expand_variables(input, output);

    printf("\nOriginal Token : %s\n", input);
    printf("Expanded Token : %s\n", output);

    return 0;
}
