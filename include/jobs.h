#ifndef JOBS_H
# define JOBS_H

# include "input.h"

typedef struct			s_process
{
	struct s_process	*next;
	char			**argv;
	pid_t			pid;
	char			completed;
	char			stopped;
	int			status;
}				t_process;

typedef struct			s_job
{
	struct s_job		*next;
	struct s_process	*first_process;
	char			*command;
	pid_t			pgid;
	char			notified;
	struct termios		tmodes;
	int			stdin;
	int			stdout;
	int			stderr;
}				t_job;

/*
**	Globals needed
*/

extern t_job			*g_job = NULL;
extern pid_t			shell_pgid;
extern struct termios		shell_tmodes;
extern int			shell_term;
extern int			shell_interactive;

/*
**	Utilities (details inside c files)
*/

t_job	*find_job(pid_t pgid);
int	job_stopped(t_job *i);
int	job_completed(t_job *i);

/*
**	Initialize the shell
*/

void	init_shell();

#endif
