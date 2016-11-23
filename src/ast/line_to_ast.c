/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/23 18:31:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"
#include "ast.h"

static void	debug_print_list(t_ast *lst)
{
	t_ast	*elem;

	elem = lst;
	ft_putendl("_______________________");
	while (elem)
	{
		ft_putstrcol(elem->str, RED);
		ft_putstr(" --  ");
		ft_putstr(YELLOW);
		ft_putnbr(elem->operator);
		ft_putendl(COLOR_RESET);
		elem = elem->right;
	}
	ft_putendl("_______________________");
}

static void	debug_print_tree(t_ast *root, int color)
{
	if (!root)
		return ;
	ft_putendlcol(root->str, color == 1 ? YELLOW: CYAN);
	debug_print_tree(root->left, 1);
	debug_print_tree(root->right, 0);
}

int			line_to_ast(t_shell *sh, char *line)
{
	t_ast	*lst_tokens;
	t_ast	*tree;

	(void)sh;
	lst_tokens = create_tokens(line);
	/* parse tokens */
	/* fill structures*/ // -> If it is not yet filled (here or in create_tokens() ?)
	/*
		No more > < >> in list;
		Only t_command | t_command && t_command
	*/
	debug_print_list(lst_tokens);
	tree = ast_create_tree_with_cmdwr(lst_tokens);
	// if (lst_tokens->right != NULL)
		// lst_tokens = ast_list_to_tree(&lst_tokens);
	/* ast to exec ? */
	if (0)
	debug_print_tree(lst_tokens, 1);
	return (GOOD);
}
