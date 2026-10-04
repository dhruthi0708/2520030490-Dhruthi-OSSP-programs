#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig)
{
    printf("\nSIGINT received. Signal handler executed.\n");
}

int main()
{
    signal(SIGINT, handle_sigint);

    printf("SIGINT handler registered.\n");
    printf("PID: %d\n", getpid());
    printf("Press Ctrl+C to test the signal.\n");

    sleep(5);

    printf("Program completed safely.\n");

    return 0;
}
