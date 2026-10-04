#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *data;
    int i;

    data = malloc(5 * sizeof(int));

    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < 5; i++)
    {
        data[i] = (i + 1) * 10;
    }

    printf("Allocated values: ");

    for (i = 0; i < 5; i++)
    {
        printf("%d ", data[i]);
    }

    printf("\n");

    free(data);

    printf("Memory released successfully.\n");

    return 0;
}
