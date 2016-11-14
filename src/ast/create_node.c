/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:55:16 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/14 18:20:29 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_42sh.h"

t_ast		*create_node(char *str)
{
	t_ast	*new;

	if (!(new = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	if (!(new->str = ft_strtrim(str)))
		return (NULL);
	return (new);
}
