/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:58:09 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/25 20:55:20 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"

static int	parse_error(const char *str)
{
	ft_putstr_fd("42sh: parse error near `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}
/*
static int	is_operator(char *str, int i, _Bool check, _Bool *word)
{
	static const char	*redir[] = {"<<", ">>", ">", "<", NULL};
	int					j;

	j = -1;
	ft_printf("^RED^%i^EOC^ -- %i -> |%s|\n", *word, check, str + i);
	while (redir[++j])
		if (ft_strnequ(redir[j], str + i, ft_strlen(redir[j])))
		{
			if (check && *word == false)
			{
				ft_putendlcol(str + i, GREEN);
				return (parse_error(redir[j]));
			}
			if (check)
				cmdwr_check_redirections(str, &i, j);
			return (1);
		}
	if (check)
		*word = false;
	return (0);
}

static int	parse_str(char *str)
{
	int					i;
	_Bool				word;

	i = 0;
	word = false;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] != '\\') && (str[i] == '\'' || str[i] == '\"'))
		{
			i += tl_jump_to_other_quote(str + i);
			word = true;
		}
		if (is_operator(str, i, true, &word) == -1)
			return (-1);
		if (!tl_iswhitespace(str[i]))
		{
			ft_putnbrendl(!ft_isdigit(str[i]) || (ft_isdigit(str[i]) && !is_operator(str, i + 1, false, &word)));
			if (!ft_isdigit(str[i]) || (ft_isdigit(str[i]) && !is_operator(str, i + 1, false, &word)))
				word = true;
		}
		i++;
	}
	return (word ? GOOD : -1);
}
*/
int		ast_parse_tree(t_ast *root)
{
	int					n_link;

	if (!root)
		return (GOOD);
	n_link = 0;
	if (root->operator == COMMAND)
	{
		// if (parse_str(root->str) == -1)
			// return (ERROR);
		return (GOOD);
	}
	else
	{
		if (root->left)
			n_link++;
		if (root->right)
			n_link++;
		return (n_link != 2 && parse_error(root->str) == -1 ? ERROR : GOOD);
	}
	return (GOOD);
}
