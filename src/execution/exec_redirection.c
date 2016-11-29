/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:07:16 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/28 23:17:25 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int		exec_redirection(t_shell *sh, t_cmdwr *r)
{
	int		id;
	int		tmp;

	if (!r->redirs)
		return (exec_command(sh, r->command));
	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		sh->last_return = get_command_status_code(tmp);
		return (sh->last_return);
	}
	else if (id == 0)
	{
		close_and_redirects(&r->redirs);
		exit(exec_command(sh, r->command));
	}
	return (0);
}
