/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_history_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:48:57 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/05 18:41:21 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include "ft_42sh.h"
#include "history.h"
#include "libft.h"
#include "tools.h"

static int		save_history(t_history *lst_history, t_variable *lst_env)
{
	int			fd;
	char		*path;

	if ((path = sh_getenv(lst_env, "HOME")))
		path = tl_str3join(path, "/", HISTORY);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
	ft_strdel(&path);
	if (fd == -1)
		return (GOOD);
	while (lst_history)
	{
		ft_putendl_fd(lst_history->command_line, fd);
		lst_history = lst_history->next;
	}
	if (close(fd) == -1)
		return (ERROR);
	return (GOOD);
}

void			clear_history_list(t_history **lst_history, t_variable *lst_env)
{
	t_history	*p;
	t_history	*elem;

	if (!(save_history(*lst_history, lst_env)))
		return ;
	p = *lst_history;
	while (p)
	{
		elem = p;
		p = p->next;
		ft_strdel(&elem->command_line);
		ft_memdel((void*)&elem);
	}
}
