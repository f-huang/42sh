/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:09:44 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/17 15:18:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"

static	int		isworddigit(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !tl_iswhitespace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (0);
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
	if (!ptr[i] || !(i += isworddigit(ptr + i)))
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
	if (ptr[tmp] == '&' || (operator == 4 && ptr[tmp] == '|'))
	{
		len++;
		if (ptr[tmp] == '&')
		{
			if ((ptr[tmp + 1] == '-') || (operator == 4 && ptr[tmp + 1] == '|'))
				len++;
			else
				len += get_to_fd(ptr + tmp + 1);
		}
	}
	return (len);
}
