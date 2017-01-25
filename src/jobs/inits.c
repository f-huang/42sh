#include "jobs.h"

/*
**	Report to include/jobs.h
*/

pid_t		shell_pgid;
struct termios	shell_tmodes;
int		shell_term;
int		shell_interactive;

/*
**	Initialize the shell, make sure it's running foreground
*/

void	init_shell()
{
	shell_term = STDIN_FILENO;
	shell_interactive = isatty(shell_term);

	if (shell_interactive)
	{
		while (tcgetpgrp(shell_term) != (shell_pgid = getpgrp()))
			kill (-shell_pgid, SIGTTIN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		shell_pgid = getpid();
		setpgid(shell_pgid, shell_pgid)
		tcsetpgrp(shell_term, shell_pgid);
		tcgetattr(shell_term, &shell_tmodes);
	}
}
