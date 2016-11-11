/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:46:09 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/11 16:24:30 by yfuks            ###   ########.fr       */
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

int				exec_execute_command(t_exec *ex, t_shell *sh, char **command)
{
	pid_t			id;
	int				tmp;
	extern	char	**environ;

	if (ex->builtin_not_binary)
	{
		ft_putstr(command[0]);
		ft_putendl(" is a builtin not binary (TODO!)");
		return (0);
	}
	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		sh->last_return = get_command_status_code(tmp);
		return (sh->last_return);
	}
	else if (id == 0)
	{
		execve(ex->command, command, environ);
		exit(NOTFOUND);
	}
	return (0);
}
