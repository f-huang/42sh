/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 16:10:39 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/16 18:04:42 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"

static size_t jump_to_other_quote(char *ptr)
{
	char	c;
	size_t	i;

	i = 0;
	c = ptr[i++];
	while (ptr[i] && ptr[i] != c && ptr[i - 1] != '\\')
		i++;
	return (i);
}

static int	create_elem(t_ast **lst, int operator, char *str)
{
	t_ast	*new;
	t_ast	*ptr;
	char	*tmp;

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

static int	is_operator(t_ast **lst_tokens, char **ptr, char *tmp)
{
	int		i;

	i = 0;
	while ((*ptr == tmp || *(*ptr - 1) != '\\') && g_operators[i].operator)
	{
		if (ft_strnequ(g_operators[i].operator, *ptr, g_operators[i].len))
		{
			create_elem(lst_tokens, -1, ft_strndup(tmp, (size_t)(*ptr - tmp)));
			create_elem(lst_tokens, i, ft_strndup(*ptr, g_operators[i].len));
			*ptr += g_operators[i].len;
			return (i);
		}
		i++;
	}
	return (-1);
}

t_ast		*create_tokens(char *line)
{
	t_ast	*lst_tokens;
	char	*ptr;
	char	*tmp;

	lst_tokens = NULL;
	ptr = line;
	tmp = ptr;
	while (*ptr)
	{
		if ((ptr == line || *ptr - 1 != '\\') && (*ptr == '\'' || *ptr == '\"'))
			ptr += jump_to_other_quote(ptr) + 1;
		else if (is_operator(&lst_tokens, &ptr, tmp) != -1)
			tmp = ptr;
		else
			ptr++;
	}
	if (tmp != ptr)
		create_elem(&lst_tokens, -1, ft_strndup(tmp, (size_t)(ptr - tmp)));
	return (lst_tokens);
}
