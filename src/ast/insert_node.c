/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:09:45 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/14 18:14:29 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	insert_node(t_ast **root, int operator, char *str, int	left)
{
	t_ast	*new;

	if (!(new = create_node(str)))
		return ;
	if (!*root)
		*root = new;
	else
	{
		left == 0 ? insert_node(&(*root)->right, operator, str, left) :\
			insert_node(&(*root)->left, operator, str, left);
	}
}
