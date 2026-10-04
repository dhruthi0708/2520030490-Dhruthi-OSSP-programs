#include <stdio.h>
#include <string.h>

#define MAX 200

int main()
{
    char input[MAX];
    char result[MAX];
    int i = 0, j = 0;

    printf("===== Single Quote Parser =====\n");
    printf("Enter text inside single quotes: ");

    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';

    /* Check for single quotes */
    if (input[0] != '\'' ||
        input[strlen(input) - 1] != '\'')
    {
        printf("Error: Input must be enclosed in single quotes.\n");
        return 1;
    }

    /* Remove the single quotes */
    i = 1;

    while (input[i] != '\0' &&
           input[i] != '\'' &&
           j < MAX - 1)
    {
        result[j++] = input[i++];
    }

    result[j] = '\0';

    /* Validate closing quote */
    if (input[i] != '\'')
    {
        printf("Error: Missing closing single quote.\n");
        return 1;
    }

    printf("\nOriginal Input : %s\n", input);
    printf("Parsed Content : %s\n", result);

    printf("\nSingle quotes preserve the literal content.\n");
    printf("Variable expansion is ignored inside single quotes.\n");

    return 0;
}
