/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:24:30 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/10 19:11:36 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		exec_is_command(t_exec *ex, t_shell *sh, char **command, char **path)
{
	if (exec_is_builtin(ex, sh, command))
		return (1);
	if (exec_is_standalone(ex, sh, command, path))
		return (1);
	return (0);
}
