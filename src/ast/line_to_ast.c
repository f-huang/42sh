/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/22 23:04:42 by FannyHuang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"
#include "ast.h"

static void	debug_print_list(t_ast *lst)
{
	t_ast	*elem;

	elem = lst;
	while (elem)
	{
		ft_putstrcol(elem->str, RED);
		ft_putstr(" --  ");
		ft_putstr(YELLOW);
		ft_putnbr(elem->operator);
		ft_putendl(COLOR_RESET);
		elem = elem->right.tree;
	}
}

static void	debug_print_tree(t_ast *root, int color)
{
	if (!root)
		return ;
	ft_putendlcol(root->str, color == 1 ? YELLOW: CYAN);
	debug_print_tree(root->left.tree, 1);
	debug_print_tree(root->right.tree, 0);
}

int			line_to_ast(t_shell *sh, char *line)
{
	t_ast	*lst_tokens;

	lst_tokens = create_tokens(line);
	/* parse tokens */
	/* fill structures*/ // -> If it is not yet filled (here or in create_tokens() ?)
	/*
		No more > < >> in list;
		Only t_command | t_command && t_command
	*/
	debug_print_list(lst_tokens);

	if (lst_tokens->right.tree != NULL)
		ast_list_to_tree(&lst_tokens);
	/* ast to exec ? */
	debug_print_tree(sh->root, 1);
	return (GOOD);
}
