/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:46:09 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/10 19:11:54 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/wait.h>
#include <stdlib.h>
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

void			exec_execute_command(t_exec *ex, t_shell *sh, char **command)
{
	pid_t	id;
	int		 status;
	int		tmp;
	extern	char	**environ;

	if (ex->builtin_not_binary)
	{
		ft_putendl("todo: not binary builtin");
		return ;
	}
	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		sh->last_return = get_command_status_code(tmp);
	}
	else if (id == 0)
	{
		execve(ex->command, command, environ);
		exit(NOTFOUND);
	}
}
