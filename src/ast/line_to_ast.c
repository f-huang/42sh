/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/14 19:26:40 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"

static const t_operator	g_operators[] = {
	{">", 1},
	{"<", 1},
	{"|", 1},
	{"<<", 2},
	{">>", 2},
	{"||", 2},
	{"&&", 2},
	{NULL, 0},
};

static void	print_tree(t_ast *root, int color)
{
	if (!root)
		return ;
	ft_putendlcol(root->str, color == 1 ? YELLOW: CYAN);
	print_tree(root->left, 1);
	print_tree(root->right, 0);
}

static int	is_operator(char *line)
{
	int		i;

	i = 0;
	while (g_operators[i].operator)
	{
		if (ft_strnequ(g_operators[i].operator, line, g_operators[i].len))
			return (i);
		i++;
	}
	return (-1);
}

static int	create_leaves(t_shell *sh, char *line, int i, int left)
{
	int		operator;
	int		tmp;
	char	*right;

	if (i < 0)
		return (GOOD);
	tmp = i;
	while (tmp > 0)
	{
		if ((operator = is_operator(line + tmp)) != -1)
		{
			insert_node(&sh->root, operator, g_operators[operator].operator, left);
			if (!(right = ft_strndup(line + tmp, i - tmp + 1)))
				return (ERROR);
			insert_node(&sh->root, -1, right, left);
			ft_strdel(&right);
			break ;
		}
		tmp--;
	}
	return (create_leaves(sh, line, tmp - 1, left == 0 ? 1 : 0));
}

int			line_to_ast(t_shell *sh, char *line)
{
	int		i;

	i = ft_strlen(line) - 1;
	if (!create_leaves(sh, line, i, 0))
		return (ERROR);
	print_tree(sh->root, 1);
	return (GOOD);
}
