/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:43:41 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/05 17:58:13 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"
#include "history.h"

static void		push_back(t_history **lst_history, t_history *new_elem)
{
	t_history	*p;

	if (*lst_history)
	{
		p = *lst_history;
		while (p->next)
			p = p->next;
		p->next = new_elem;
	}
	else
		*lst_history = new_elem;
}

int			save_command_line(t_history **lst_history, char *command_line)
{
	t_history	*new_elem;

	if (!command_line)
		return (ERROR);
	if (!(new_elem = (t_history*)ft_memalloc(sizeof(t_history))))
		return (ERROR);
	if (!(new_elem->command_line = ft_strdup(command_line)))
		return (ERROR);
	push_back(lst_history, new_elem);
	return (GOOD);
}