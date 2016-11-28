/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:23:14 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/25 19:51:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "tools.h"
#include "libft.h"

static int	get_operator(int operator)
{
	if (operator == 0)
		return (AND);
	else if (operator == 1)
		return (OR);
	else if (operator == 2)
		return (PIPE);
	return (COMMAND);
}

int			ast_create_elem(t_ast **lst, int operator, char *str)
{
	t_ast	*new;
	char	*tmp;

	if (tl_isstrempty(str))
	{
		ft_strdel(&str);
		return (GOOD);
	}
	if (!(new = (t_ast*)ft_memalloc(sizeof(t_ast))))
		return (ERROR);
	tmp = str;
	new->str = ft_strtrim(str);
	ft_strdel(&tmp);
	new->operator = get_operator(operator);
	new->cmd1 = NULL;
	new->cmd2 = NULL;
	ast_insert_elem_in_tree(lst, new);
	return (GOOD);
}
