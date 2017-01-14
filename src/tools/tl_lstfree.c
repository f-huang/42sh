/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:54:52 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/14 16:10:09 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		tl_lstfree(t_list **begin)
{
	t_list	*cursor;
	t_list	*tofree;

	cursor = *begin;
	while (cursor)
	{
		tofree = cursor;
		cursor = cursor->next;
		free(tofree);
	}
}
