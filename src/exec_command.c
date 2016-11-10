/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:00:09 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/10 20:05:26 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "execution.h"
#include "tools.h"
#include "libft.h"

int		exec_command(t_shell *sh, char **command)
{
	char	**paths;
	t_exec	ex;

	if (!(paths = exec_get_envpath(sh, command)))
		return (ERROR);
	ex.builtin_not_binary = 0;
	ex.command = 0;
	if (!exec_is_command(&ex, sh, command, paths))
	{
		sh->last_return = NOTFOUND;
		tl_freedoubletab(paths);
		return (exec_print_command_error(NOTFOUND, command[0]));
	}
	if (!ex.builtin_not_binary && !exec_is_executable(ex.command))
	{
		sh->last_return = NOTFOUND;
		tl_freedoubletab(paths);
		ft_strdel(&ex.command);
		return (exec_print_command_error(CANNOTINVOKE, ex.command));
	}
	exec_execute_command(&ex, sh, command);
	exec_print_command_error(sh->last_return, ex.command);
	ft_strdel(&ex.command);
	tl_freedoubletab(paths);
	return (GOOD);
}
