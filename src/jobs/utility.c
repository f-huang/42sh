#include "jobs.h"

t_job	*g_job = NULL;

/*
**	Find active job from the pgid or return NULL
*/

t_job	*find_job(pid_t pgid)
{
	t_job	*i;

	i = g_job;
	while (i)
	{
		if (i->pgid == pgid)
			return (i);
		i = i->next;
	}
	return (NULL); 
}

/*
**	Return true if all processes in the job have stopped or completed
*/

int	job_stopped(t_job *i)
{
	t_process	*p;

	p = i->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0)
		p = p->next;
	}
	return (1);
}

/*
**	Return true if all processes in the job have completed successfully
*/

int	job_completed(t_job *i)
{
	t_process	*p;

	p = i->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
