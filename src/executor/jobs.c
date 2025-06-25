#include "../../includes/minishell.h"

typedef struct s_job
{
    int             id;
    pid_t           pid;
    char            *cmdline;
    struct s_job    *next;
}               t_job;

static t_job    *g_jobs = NULL;
static int      g_next_id = 1;

void    add_job(pid_t pid, char *cmdline)
{
    t_job  *new = malloc(sizeof(t_job));
    if (!new)
        return ;
    new->id = g_next_id++;
    new->pid = pid;
    new->cmdline = ft_strdup(cmdline);
    new->next = g_jobs;
    g_jobs = new;
    printf("[%d] %d\n", new->id, pid);
}

static void remove_job(pid_t pid)
{
    t_job **prev = &g_jobs;
    t_job *cur = g_jobs;
    while (cur)
    {
        if (cur->pid == pid)
        {
            *prev = cur->next;
            free(cur->cmdline);
            free(cur);
            return ;
        }
        prev = &cur->next;
        cur = cur->next;
    }
}

void    check_jobs(void)
{
    t_job  *job = g_jobs;
    int     status;
    pid_t   ret;

    while (job)
    {
        ret = waitpid(job->pid, &status, WNOHANG);
        if (ret > 0)
        {
            printf("[%d] Done %s\n", job->id, job->cmdline);
            remove_job(job->pid);
            job = g_jobs;
        }
        else
            job = job->next;
    }
}

void    print_jobs(void)
{
    t_job  *job = g_jobs;
    while (job)
    {
        printf("[%d] Running %s\n", job->id, job->cmdline);
        job = job->next;
    }
}

static t_job    *find_job(int id)
{
    t_job *job = g_jobs;
    while (job)
    {
        if (job->id == id)
            return (job);
        job = job->next;
    }
    return (NULL);
}

void    bring_job_foreground(int id)
{
    t_job *job = find_job(id);
    int    status;

    if (!job)
    {
        printf("fg: job %d not found\n", id);
        return ;
    }
    tcsetpgrp(STDIN_FILENO, job->pid);
    kill(job->pid, SIGCONT);
    waitpid(job->pid, &status, 0);
    tcsetpgrp(STDIN_FILENO, getpid());
    remove_job(job->pid);
    g_last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

void    continue_job_background(int id)
{
    t_job *job = find_job(id);
    if (!job)
    {
        printf("bg: job %d not found\n", id);
        return ;
    }
    kill(job->pid, SIGCONT);
}


