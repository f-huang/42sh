/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:21:06 by fhuang            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/12/05 18:40:24 by cjacquem         ###   ########.fr       */
=======
/*   Updated: 2016/11/30 15:15:23 by cjacquem         ###   ########.fr       */
>>>>>>> 72c4042b0eecd6045b65c415a4cbc45cafb5c815
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_42sh.h"
#include "environment.h"
#include "history.h"

/*
**	This function free every variable in the shell structure
**	and set pointers to NULL.
*/

static int			save_history(t_list *all_history)
{
	int		fd;

	fd = open(HISTORY, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,\
												S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (ERROR);
	while (all_history)
	{
		write(fd, all_history->content, all_history->content_size);
		write(fd, "\n", 1);
		all_history = all_history->next;
	}
	if (close(fd) == -1)
		return (ERROR);
	return (GOOD);
}

void	clear_shell(t_shell *sh)
{
	save_history(sh->all_history);
	sh->last_return = 0;
	clear_history_list(&sh->lst_history, sh->lst_env);
	clear_env_list(&sh->lst_env);
	clear_env_list(&sh->lst_localvar);
	ft_strdel(&sh->bin_path);
}
