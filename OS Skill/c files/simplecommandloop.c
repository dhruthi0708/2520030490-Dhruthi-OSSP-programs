#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char command[200];

    while (1) {
        printf("sri_dhruthi_shell@Dhruthi $ ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        // Exit shell
        if (strcmp(command, "exit") == 0) {
            printf("Shell terminated.\n");
            break;
        }

        // Empty command
        if (strlen(command) == 0) {
            continue;
        }

        // Execute Linux command
        system(command);
    }

    return 0;
}
