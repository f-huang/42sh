/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 10:31:53 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/24 10:35:02 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"

void		tl_lstaddend(t_list **alst, t_list *new_elem)
{
	t_list	*p;

	if (!new_elem)
		return ;
	if (!(*alst))
		*alst = new_elem;
	else
	{
		p = tl_lstlast(*alst);
		p->next = new_elem;
		new_elem->prev = p;
	}
}
