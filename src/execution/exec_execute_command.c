/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:46:09 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/11 18:55:03 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "environment.h"

static	const	t_bnb	g_bnb[] = {
	{"cd", builtin_cd},
	{"exit", builtin_exit},
	{"unsetenv", builtin_unsetenv},
	{"setenv", builtin_setenv},
	{0, 0}
};

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

static	int		get_ac(char **command)
{
	int		i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

static	int		execute_bnb(t_shell *sh, char **command)
{
	int		i;

	i = 0;
	while (g_bnb[i].builtin)
	{
		if (ft_strcmp(g_bnb[i].builtin, command[0]) == 0)
		{
			sh->last_return = g_bnb[i].function(sh, get_ac(command), command);
			return (sh->last_return);
		}
		i++;
	}
	return (0);
}

int				exec_execute_command(t_exec *ex, t_shell *sh, char **command)
{
	pid_t			id;
	int				tmp;
	char			**env;

	if (ex->builtin_not_binary)
		return (execute_bnb(sh, command));
	sh_setenv(&sh->lst_env, "_", ex->command);
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
		execve(ex->command, command, env);
		exit(NOTFOUND);
	}
	return (0);
}
