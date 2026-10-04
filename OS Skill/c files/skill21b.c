#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;

    file = fopen("missing.txt", "r");

    if (file == NULL)
    {
        perror("Error opening missing.txt");

        printf("Recovery: File could not be opened.\n");
        printf("Program continues safely.\n");

        return 0;
    }

    printf("File opened successfully.\n");

    fclose(file);

    return 0;
}
