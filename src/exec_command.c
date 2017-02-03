/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:00:09 by yfuks             #+#    #+#             */
/*   Updated: 2017/02/03 13:42:40 by tpoac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_42sh.h"
#include "execution.h"
#include "tools.h"
#include "libft.h"
#include "expansion.h"

static	int	print_error(char **paths, int error, char *command)
{
	tl_freedoubletab(paths);
	return (exec_print_command_error(error, command));
}

static int	clear_exec_command(t_shell *sh, char **command, char **paths,\
								t_exec *ex)
{
	exec_execute_command(ex, sh, command);
	ft_strdel(&ex->command);
	tl_freedoubletab(paths);
	return (sh->last_return);
}

int			exec_command(t_shell *sh, char **command)
{
	char	**paths;
	t_exec	ex;

	if (command[0][0] == '(')
	{
		subshell_substitution(command);
		exec_command(sh, command);
	}
	paths = exec_get_envpath(sh);
	ft_bzero(&ex, sizeof(ex));
	if (ft_strlen(command[0]) > _POSIX_ARG_MAX && (sh->last_return = 1))
		return (print_error(paths, TOOLONG, command[0]));
	if (!exec_is_command(&ex, sh, command, paths))
		return (print_error(paths, NOTFOUND, command[0]));
	if (exec_is_directory(ex.command) && !ex.builtin_not_binary)
	{
		sh->last_return = CANNOTINVOKE;
		ft_strdel(&ex.command);
		return (print_error(paths, ISDIRECTORY, command[0]));
	}
	if (!ex.builtin_not_binary && !exec_is_executable(ex.command))
	{
		sh->last_return = CANNOTINVOKE;
		ft_strdel(&ex.command);
		return (print_error(paths, CANNOTINVOKE, command[0]));
	}
	return (clear_exec_command(sh, command, paths, &ex));
}
