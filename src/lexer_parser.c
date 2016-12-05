/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:34:14 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/02 15:45:25 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**				first_lexer splits the command line in part with ; in delimiter
**				The simple and double quote and the backslash are considered.
*/

#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"

static int		add_elem(t_list **lst, char *command, size_t size)
{
	char		*tmp;
	char		*tmp_trim;
	t_list		*elem;
	t_ast		*ast;

	if (!(tmp = tl_strndup(command, size)))
		return (ERROR);
	if (!(tmp_trim = ft_strtrim(tmp)))
		return (ERROR);
	ft_strdel(&tmp);
	ast = NULL;
	if ((ast = line_to_ast(tmp_trim)))
	{
		elem = NULL;
		if (!(elem = tl_lstnew(ast, sizeof(t_ast))))
			return (ERROR);
		tl_lstaddend(lst, elem);
	}
	ft_strdel(&tmp_trim);
	return (GOOD);
}

static int		unmatched(t_bitfield *open)
{
	if (open->dquote || open->squote || open->bslash)
	{
		ft_putstr_fd("Unmatched ", 2);
		if (!open->bslash)
			ft_putchar_fd(open->dquote ? '\"' : '\'', 2);
		else
			ft_putchar_fd('\\', 2);
		ft_putendl_fd(".", 2);
		return (1);
	}
	return (0);
}

static int		check_n_save(t_list **lst, char *command, size_t size,\
															t_bitfield *open)
{
	if (unmatched(open) || !(add_elem(lst, command, size)))
	{
		if (*lst)
			tl_lstdelast(lst);
		return (ERROR);
	}
	return (GOOD);
}

static int		check_inhibitors(t_list **lst, char *c, size_t *i, t_bitfield *open)
{
	if (c[*i] == '\\')
	{
		if (c[*i + 1] == 0)
		{
			open->bslash |= 1;
			if (*lst)
				tl_lstdelast(lst);
			unmatched(open);
			return (ERROR);
		}
		(*i)++;
	}
	if ((c[*i] == '\'' || c[*i] == '\"') &&\
		(*i == 0 || (*i > 0 && c[*i - 1] != '\\')))
	{
		*i += tl_jump_to_other_quote(c + *i);
		c[*i] == '\'' ? (open->squote ^= 1) : (open->dquote ^= 1);
		if (c[*i] == 0)
		{
			if (*lst)
				tl_lstdelast(lst);
			unmatched(open);
			return (ERROR);
		}
		c[*i] == '\'' ? (open->squote ^= 1) : (open->dquote ^= 1);
	}
	return (GOOD);
}

int				lexer_parser(char *command_line, t_list **lst)
{
	size_t		i;
	size_t		index;
	t_bitfield	open;

	i = 0;
	index = 0;
	open.squote = 0;
	open.dquote = 0;
	while (command_line[i])
	{
		if (!check_inhibitors(lst, command_line, &i, &open))
			return (ERROR);
		if (command_line[i] == ';' && !open.squote && !open.dquote)
		{
			if (check_n_save(lst, &command_line[index], i - index, &open))
				index = i + 1;
			else
				return (ERROR);
		}
		++i;
	}
	if (i != index)
		return (check_n_save(lst, &command_line[index], i - index, &open));
	return (GOOD);
}