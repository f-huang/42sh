/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:23:14 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/18 11:32:15 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "tools.h"
#include "libft.h"

static int	isstrempty(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!tl_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			ast_create_elem(t_ast **lst, int operator, char *str)
{
	t_ast	*new;
	t_ast	*ptr;
	char	*tmp;

	if (isstrempty(str))
		return (GOOD);
	if (!(new = (t_ast*)ft_memalloc(sizeof(t_ast))))
		return (ERROR);
	tmp = str;
	new->str = ft_strtrim(str);
	ft_strdel(&tmp);
	new->operator = operator;
	if (!*lst)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->right)
			ptr = ptr->right;
		new->left = ptr;
		ptr->right = new;
	}
	return (GOOD);
}
