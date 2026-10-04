#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_JOBS 5

typedef enum
{
    RUNNING,
    COMPLETED
} JobState;

typedef struct
{
    int pid;
    int pgid;
    JobState state;
} Job;

Job jobs[MAX_JOBS];
int job_count = 0;

void add_job(int pid, int pgid)
{
    if (job_count < MAX_JOBS)
    {
        jobs[job_count].pid = pid;
        jobs[job_count].pgid = pgid;
        jobs[job_count].state = RUNNING;
        job_count++;
    }
}

void update_jobs()
{
    int i;
    int status;

    for (i = 0; i < job_count; i++)
    {
        if (jobs[i].state == RUNNING)
        {
            if (waitpid(jobs[i].pid, &status, WNOHANG) > 0)
            {
                jobs[i].state = COMPLETED;
            }
        }
    }
}

void remove_completed_jobs()
{
    int i, j;

    for (i = 0; i < job_count;)
    {
        if (jobs[i].state == COMPLETED)
        {
            for (j = i; j < job_count - 1; j++)
            {
                jobs[j] = jobs[j + 1];
            }

            job_count--;
        }
        else
        {
            i++;
        }
    }
}

void show_jobs()
{
    int i;

    printf("\nJob Table:\n");

    for (i = 0; i < job_count; i++)
    {
        printf("PID: %d | PGID: %d | State: %s\n",
               jobs[i].pid,
               jobs[i].pgid,
               jobs[i].state == RUNNING ? "RUNNING" : "COMPLETED");
    }

    if (job_count == 0)
    {
        printf("No active jobs.\n");
    }
}

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0)
    {
        sleep(3);
        return 0;
    }

    add_job(pid1, pid1);

    pid2 = fork();

    if (pid2 == 0)
    {
        sleep(5);
        return 0;
    }

    add_job(pid2, pid2);

    show_jobs();

    sleep(4);

    update_jobs();

    printf("\nAfter status update:\n");
    show_jobs();

    remove_completed_jobs();

    printf("\nAfter removing completed jobs:\n");
    show_jobs();

    while (job_count > 0)
    {
        update_jobs();
        remove_completed_jobs();
        sleep(1);
    }

    printf("\nAll jobs completed and removed.\n");

    return 0;
}
