/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:23:14 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/24 13:10:49 by fhuang           ###   ########.fr       */
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

static int	get_operator(int operator)
{
	if (operator == 0)
		return (OR);
	else if (operator == 1)
		return (AND);
	else if (operator == 2)
		return (HEREDOC);
	else if (IS_REDIRECTION(operator))
		return (operator);
	else if (operator == 6)
		return (PIPE);
	return (COMMAND);
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
	new->operator = get_operator(operator);
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
