/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:00:09 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/14 18:27:02 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "execution.h"
#include "tools.h"
#include "libft.h"

static	int	print_error(char **paths, int error, char *command)
{
	tl_freedoubletab(paths);
	return (exec_print_command_error(error, command));
}

int			exec_command(t_shell *sh, char **command)
{
	char	**paths;
	t_exec	ex;

	if (!(paths = exec_get_envpath(sh)))
		return (ERROR);
	ex.builtin_not_binary = 0;
	ex.command = 0;
	if (!exec_is_command(&ex, sh, command, paths))
		return (print_error(paths, NOTFOUND, command[0]));
	if (exec_is_directory(ex.command))
	{
		ft_strdel(&ex.command);
		return (print_error(paths, ISDIRECTORY, ex.command));
	}
	if (!ex.builtin_not_binary && !exec_is_executable(ex.command))
	{
		sh->last_return = CANNOTINVOKE;
		ft_strdel(&ex.command);
		return (print_error(paths, CANNOTINVOKE, command[0]));
	}
	exec_execute_command(&ex, sh, command);
	ft_strdel(&ex.command);
	tl_freedoubletab(paths);
	return (GOOD);
}
