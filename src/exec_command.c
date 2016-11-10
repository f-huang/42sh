/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:00:09 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/10 19:11:33 by yfuks            ###   ########.fr       */
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
	if (!exec_is_command(&ex, sh, command, paths))
		return (NOTFOUND);
	if (!ex.builtin_not_binary && !exec_is_executable(ex.command))
		return (CANNOTINVOKE);
	exec_execute_command(&ex, sh, command);
	ft_strdel(&ex.command);
	tl_freedoubletab(paths);
	return (GOOD);
}
