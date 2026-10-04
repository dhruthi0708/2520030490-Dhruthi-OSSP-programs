#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

int main()
{
    char current_dir[PATH_MAX];
    char previous_dir[PATH_MAX];
    char path[PATH_MAX];

    /* Get initial working directory */
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    strcpy(previous_dir, current_dir);

    printf("===== Directory Navigation =====\n");
    printf("Type 'pwd' to show current directory\n");
    printf("Type 'cd <path>' to change directory\n");
    printf("Type 'prev' to return to previous directory\n");
    printf("Type 'exit' to quit\n");

    while (1)
    {
        printf("\n$ ");

        char command[PATH_MAX];

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = '\0';

        /* Exit */
        if (strcmp(command, "exit") == 0)
        {
            break;
        }

        /* Show current directory */
        if (strcmp(command, "pwd") == 0)
        {
            if (getcwd(current_dir, sizeof(current_dir)) != NULL)
                printf("Current Directory: %s\n", current_dir);
            else
                perror("getcwd");

            continue;
        }

        /* Go to previous directory */
        if (strcmp(command, "prev") == 0)
        {
            if (chdir(previous_dir) == 0)
            {
                char temp[PATH_MAX];

                strcpy(temp, current_dir);
                strcpy(current_dir, previous_dir);
                strcpy(previous_dir, temp);

                printf("Changed to previous directory: %s\n",
                       current_dir);
            }
            else
            {
                perror("prev");
            }

            continue;
        }

        /* Change directory */
        if (strncmp(command, "cd ", 3) == 0)
        {
            strcpy(path, command + 3);

            /* Validate path before changing */
            if (access(path, F_OK) != 0)
            {
                printf("Error: Path does not exist.\n");
                continue;
            }

            if (access(path, X_OK) != 0)
            {
                printf("Error: Permission denied.\n");
                continue;
            }

            /* Store current directory */
            if (getcwd(current_dir, sizeof(current_dir)) == NULL)
            {
                perror("getcwd");
                continue;
            }

            /* Change directory */
            if (chdir(path) == 0)
            {
                strcpy(previous_dir, current_dir);

                if (getcwd(current_dir, sizeof(current_dir)) != NULL)
                {
                    printf("Directory changed successfully.\n");
                    printf("Current Directory: %s\n",
                           current_dir);
                }
            }
            else
            {
                perror("cd");
            }

            continue;
        }

        printf("Invalid command.\n");
    }

    printf("\nProgram terminated.\n");

    return 0;
}
