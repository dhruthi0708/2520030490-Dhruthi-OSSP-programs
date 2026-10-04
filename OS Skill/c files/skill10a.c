#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main()
{
    char current_dir[PATH_MAX];
    FILE *state_file;

    printf("===== Shell State and Exit =====\n");

    /* Retrieve current directory */
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    /* Display current path */
    printf("Current Directory: %s\n", current_dir);

    /* Save state */
    state_file = fopen("shell_state.txt", "w");

    if (state_file == NULL)
    {
        perror("fopen");
        return 1;
    }

    fprintf(state_file, "Last Directory: %s\n", current_dir);

    printf("Shell state saved successfully.\n");

    /* Cleanup resource */
    fclose(state_file);

    printf("State file closed.\n");

    /* Process exit request */
    char choice;

    printf("\nDo you want to exit? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        printf("Cleaning up resources...\n");
        printf("Exiting program safely.\n");
        exit(0);
    }

    printf("Program continues running.\n");

    return 0;
}
