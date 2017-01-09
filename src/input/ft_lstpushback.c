/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:13:35 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:47:33 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_lstpushback(t_list **lst, void const *content, size_t content_size)
{
	t_list	*list;

	list = *lst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_lstnew(content, content_size);
	}
	else
		*lst = ft_lstnew(content, content_size);
}
