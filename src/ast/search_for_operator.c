/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 12:00:26 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/18 14:46:21 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast	*ast_search_for_operator(t_ast *lst_tokens, _Bool prio, _Bool right)
{
	t_ast	*elem;

	elem = lst_tokens;
	while (elem)
	{
		if (prio && elem->operator >= 0 && elem->operator < 2)
			return (elem);
		else if (!prio && elem->operator > 1 && elem->operator < 7)
			return (elem);
		elem = (right ? elem->right : elem->left);
	}
	return (NULL);
}
