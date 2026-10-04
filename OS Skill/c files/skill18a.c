#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("SIGINT is blocked.\n");
    printf("PID: %d\n", getpid());
    printf("Try pressing Ctrl+C now.\n");

    sleep(5);

    printf("\nUnblocking SIGINT...\n");

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    printf("SIGINT is now unblocked.\n");
    printf("Signal mask test completed.\n");

    return 0;
}
