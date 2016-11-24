/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 07:08:36 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/24 11:10:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

void		ast_remove_link(t_ast **lst, t_ast *link)
{
	t_ast		*ptr;
	t_ast		*prev;

	ptr = *lst;
	prev = NULL;
	while (ptr)
	{
		if (ptr == link)
		{
			if (prev)
				prev->right = link->right;
			else
				*lst = link->right;
			if (link->right)
				link->right->left = prev;
			ft_strdel(&link->str);
			ft_memdel((void*)&link);
			return ;
		}
		prev = ptr;
		ptr = ptr->right;
	}
}
