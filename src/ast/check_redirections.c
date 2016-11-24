/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:09:44 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/24 09:25:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"

static size_t	jump_to_other_quote(char *ptr)
{
	char	c;
	size_t	i;

	i = 0;
	c = ptr[i++];
	while (ptr[i] && ptr[i] != c && ptr[i - 1] != '\\')
		i++;
	return (i);
}

static	int		get_word(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !tl_iswhitespace(str[i]))
	{
		if ((i == 0 || str[i - 1] != '\\') && (str[i] == '\'' || str[i] == '\"'))
			i+= jump_to_other_quote(str + i);
		i++;
	}
	return (i);
}

static size_t	get_to_fd(char *ptr)
{
	int		i;

	i = 0;
	while (ptr[i] && tl_iswhitespace(ptr[i]))
		i++;
	if (!ptr[i] || !(i += get_word(ptr + i)))
		return (0);
	return (i);
}

size_t	ast_check_redirections(int operator, char *ptr, size_t *i)
{
	size_t	len;
	size_t	tmp;

	len = 0;
	tmp = *i + (operator == 3 ? 2 : 1);
	if (operator == 5 && ptr[tmp] == '>')
		len++;
	if ((*i == 1 || (*i > 1 && tl_iswhitespace(ptr[*i - 2]))) && ft_isdigit(ptr[*i - 1]))
	{
		len++;
		(*i)--;
	}
	if ((ptr[tmp] == '&') || (operator == 4 && ptr[tmp] == '|'))
	{
		len++;
		tmp++;
	}
	len += get_to_fd(ptr + tmp);
	return (len);
}
