/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first-lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:34:14 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/17 17:39:10 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**				first_lexer splits the command line in part with ; in delimiter
**				The simple and double quote and the backslash are considered.
*/

#include "ft_42sh.h"
#include "libft.h"

static int		add_elem(t_list **lst, char *command, size_t size)
{
	char		*tmp;
	char		*tmp_trim;
	t_list		*elem;

	if (!(tmp = ft_strndup(command, size)))
		return (ERROR);
	if (!(tmp_trim = ft_strtrim(tmp)))
		return (ERROR);
	ft_strdel(&tmp);
	if (!(elem = ft_lstnew(tmp_trim, ft_strlen(tmp_trim) + 1)))
		return (ERROR);
	ft_strdel(&tmp_trim);
	ft_lstadd(lst, elem);
	return (GOOD);
}

static int		unmatched(t_bitfield *open)
{
	if (open->dquote || open->squote)
	{
		ft_putstr_fd("Unmatched ", 2);
		ft_putchar_fd(open->dquote ? '\"' : '\'', 2);
		ft_putendl_fd(".", 2);
		return (ERROR);
	}
	return (GOOD);
}

static int		check_char(char c, size_t *i, t_bitfield *open)
{
	if (c == '\\')
		ft_strchr("abeEfnrtv\\\'\"?", c) ? i += 2 : ++i;
	else if (c == '\'')
		open->squote ^= 1;
	else if (c == '\"')
		open->dquote ^= 1;
	return (GOOD);
}

static int		check_n_save(t_list *lst, char *command, size_t size,\
															t_bitfield *open)
{
	if (!(unmatched(open)) || !(add_elem(&lst, command, size)))
	{
		if (lst)
			ft_lstdel(&lst, ft_del);
		return (ERROR);
	}
	return (GOOD);
}

t_list			*first_lexer(char *command_line)
{
	size_t		i;
	size_t		index;
	t_list		*lst;
	t_bitfield	open;

	i = 0;
	index = 0;
	lst = NULL;
	open.squote = 0;
	open.dquote = 0;
	while (command_line[i])
	{
		check_char(command_line[i], &i, &open);
		if (command_line[i] == ';' && !open.squote && !open.dquote)
		{
			check_n_save(lst, &command_line[index], i - index, &open);
			index = i + 1;
		}
		++i;
	}
	if (i != index)
		check_n_save(lst, &command_line[index], i - index, &open);
	return (lst);
}
