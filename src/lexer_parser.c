/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:34:14 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/30 15:59:03 by fhuang           ###   ########.fr       */
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
		if (!(elem = ft_lstnew(ast, sizeof(t_ast))))
			return (ERROR);
		tl_lstaddend(lst, elem);
		ast_destroy_tree(ast);
	}
	ft_strdel(&tmp_trim);
	return (GOOD);
}

static int		unmatched(t_bitfield *open)
{
	if (open->dquote || open->squote)
	{
		ft_putstr_fd("Unmatched ", 2);
		ft_putchar_fd(open->dquote ? '\"' : '\'', 2);
		ft_putendl_fd(".", 2);
		return (1);
	}
	return (0);
}

static int		check_inhibitors(char c, size_t *i, t_bitfield *open)
{
	if (c == '\\')
		ft_strchr("abeEfnrtv\\\'\"?", c) ? i += 2 : ++i;
	else if (c == '\'')
		open->squote ^= 1;
	else if (c == '\"')
		open->dquote ^= 1;
	return (GOOD);
}

static int		check_n_save(t_list **lst, char *command, size_t size,\
															t_bitfield *open)
{
	if (unmatched(open) || !(add_elem(lst, command, size)))
	{
		if (lst)
			ft_lstdel(lst, tl_del);
		return (ERROR);
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
	while (command_line[i] && check_inhibitors(command_line[i], &i, &open))
	{
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
