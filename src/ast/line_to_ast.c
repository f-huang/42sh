/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/16 17:55:12 by fhuang           ###   ########.fr       */
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
		ft_putstr(GREEN);
		ft_putnbr(elem->operator);
		ft_putendl(COLOR_RESET);
		elem = elem->right;
	}
}

static void	print_tree(t_ast *root, int color)
{
	if (!root)
		return ;
	ft_putendlcol(root->str, color == 1 ? YELLOW: CYAN);
	print_tree(root->left, 1);
	print_tree(root->right, 0);
}

int			line_to_ast(t_shell *sh, char *line)
{
	t_ast	*lst_tokens;
	/* line -> tab_commands (;) */
/*
	2)COMMANDS[i] -> LIST TOKENS
		ex : {echo -n tata tutu} {2>& -} {"test 2" titi} {&&} {&} {cat test 2}
*/
	lst_tokens = create_tokens(line);
	debug_print_list(lst_tokens);

	/* check ? */
	/* token to ast */
	/* ast to exec ? */
	print_tree(sh->root, 1);
	return (GOOD);
}
