/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:07:16 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/12 18:39:29 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include <sys/wait.h>

int		exec_redirection(t_shell *sh, t_cmdwr *r)
{
//	int		id;
//	int		tmp;

	if (!r->redirs)
		return (exec_command(sh, r->command));
	else
	{
		close_and_redirects(r, &r->redirs);
		return (exec_command(sh, r->command));
	}
/*	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		ft_putstr_fd("finish: ", 2);
		ft_putendl_fd(r->command[0], 2);
		sh->last_return = get_command_status_code(tmp);
		free_heredocs(r);
		return (sh->last_return);
	}
	else if (id == 0)
	{
		ft_putendl_fd(r->command[0], 2);
		ft_putendl_fd("close and redirs", 2);
		}*/
	return (0);
}
