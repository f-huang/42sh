/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 12:00:26 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/22 22:21:14 by FannyHuang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*ast_search_for_operator(t_ast *list, int what, _Bool right)
{
	t_ast	*elem;

	elem = list;
	while (elem)
	{
		if (elem->operator == what)
			return (elem);
		elem = (right ? elem->right.tree : elem->left.tree);
	}
	return (NULL);
}
