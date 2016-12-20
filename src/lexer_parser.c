/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:34:14 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/20 19:47:10 by fhuang           ###   ########.fr       */
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

#define QUOTE_PROMPT "quote> "

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

static int		quote_prompt(char c)
{
	ft_putstr(c == '\'' ? "s" : "d");
	ft_putstr(QUOTE_PROMPT);
	return (GOOD);
}

static int		is_line_fulfilled(char **command, char *line, size_t *i, char c)
{
	int		squote;
	int		dquote;

	if (!(*command = tl_str3join(*command, line, "\n")))
		return (ERROR);
	squote = c == '\'' ? 1 : 0;
	dquote = c == '\"' ? 1 : 0;
	while ((*command)[*i])
	{
		if ((*command)[*i] == c && *i > 1 && (*command)[*i - 1] != '\\')
		{
		}
		(*i)++;
	}
	return (open % 2 ? ERROR : GOOD);
}

static int		wait_for_end_of_quote(char **command, size_t *i, char c)
{
	char		*line;
	int			ret;

	line = NULL;
	while (quote_prompt(c) && (ret = tl_get_next_line(0, &line)) > 0)
	{
		if (is_line_fulfilled(command, line, i, c))
		{
			break ;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (ret == -1 ? ERROR : GOOD);
}

static int		check_inhibitors(t_list **lst, char **command, size_t *i)
{
	char		c;

	if ((*command)[*i] == '\\')
	{
		if ((*command)[*i + 1] == 0)
		{
			if (*lst)
				tl_lstdelast(lst);
			ft_putstr_fd("Unmatched \\.\n", 2);
			return (ERROR);
		}
		(*i)++;
	}
	if (((*command)[*i] == '\'' || (*command)[*i] == '\"') &&\
		(*i == 0 || (*i > 0 && (*command)[*i - 1] != '\\')))
	{
		c = (*command)[*i];
		*i += tl_jump_to_other_quote((*command) + *i);
		if ((*command)[*i] == 0)
		{
			wait_for_end_of_quote(command, i, c);
		}
	}
	return (GOOD);
}

int				lexer_parser(char **command_line, t_list **lst)
{
	size_t		i;
	size_t		index;

	i = -1;
	index = 0;
	while ((*command_line)[++i])
	{
		if (!check_inhibitors(lst, command_line, &i))
			return (ERROR);
		if ((*command_line)[i] == '#' &&\
			(i == 0 || (i > 0 && tl_iswhitespace((*command_line)[i - 1]))) &&\
			(i == 0 || i == 1 || (i > 1 && (*command_line)[i - 2] != '\\')))
			ft_strclr(*command_line + i);
		if ((*command_line)[i] == ';')
		{
			if (!add_elem(lst, (*command_line) + index, i - index))
				return (ERROR);
			index = i + 1;
		}
	}
	return (i != index ? add_elem(lst,\
		(*command_line) + index, i - index) : GOOD);
}
