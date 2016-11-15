/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute_right_redirect.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 01:08:40 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/15 04:29:27 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "environment.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

static	int		get_command_status_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}

/*
**	This function perform a shell right redirection
**	exemple :
**	$> echo coucou 1> test
**		(redirect stdinput in test)
**	$> echo coucou > test
**		(redirect stdinput in test)
**	$> echo coucou >&-               $> echo coucou >& -
**		(close standard outpout)
**	$> echo coucou >& 2
**		(???????)
*/

int		exec_right_redirect(t_shell *sh, t_redirection *r)
{
	pid_t		id;
	int			tmp;
	char		**env;
	int			fd;

	sh_setenv(&sh->lst_env, "_", r->executable);
	env = lstenv_to_tab(sh->lst_env);
	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		sh->last_return = get_command_status_code(tmp);
		free(env);
		return (sh->last_return);
	}
	else if (id == 0)
	{
		fd = (r->to_fd == -1) ? open(r->dest, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR) : r->to_fd;
		r->from_fd = (r->from_fd == -1) ? 1 : r->from_fd;
		dup2(fd, r->from_fd);
		if (r->to_fd == -1)
			close(fd);
		execve(r->executable, r->command, env);
		exit(NOTFOUND);
	}
	return (0);
}
