#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct
{
    int job_id;
    pid_t pid;
    char state[20];
} Job;

int main()
{
    Job jobs[2];
    pid_t p1, p2;

    p1 = fork();

    if (p1 == 0)
    {
        sleep(5);
        return 0;
    }

    p2 = fork();

    if (p2 == 0)
    {
        sleep(5);
        return 0;
    }

    jobs[0].job_id = 1;
    jobs[0].pid = p1;
    snprintf(jobs[0].state, sizeof(jobs[0].state), "RUNNING");

    jobs[1].job_id = 2;
    jobs[1].pid = p2;
    snprintf(jobs[1].state, sizeof(jobs[1].state), "RUNNING");

    printf("\nActive Jobs:\n");

    printf("[%d] PID: %d  Status: %s\n",
           jobs[0].job_id,
           jobs[0].pid,
           jobs[0].state);

    printf("[%d] PID: %d  Status: %s\n",
           jobs[1].job_id,
           jobs[1].pid,
           jobs[1].state);

    printf("\nJob listing completed.\n");

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}
