/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 10:31:53 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/28 18:27:50 by fhuang           ###   ########.fr       */
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
	}
}
