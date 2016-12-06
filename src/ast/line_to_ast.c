/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/06 11:45:27 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include "execution.h"
// static void	print_cmd(t_cmdwr *cmd)
// {
// 	for (int i = 0; cmd->command[i]; i++)
// 		ft_putendlcol(cmd->command[i], GREEN);
// 	t_redirections	*ptr;
// 	ptr = cmd->redirs;
// 	while (ptr)
// 	{
// 		if (ptr->type & SIMPLE_LEFT_REDIRECT)
// 			ft_putendl("<");
// 		else if (ptr->type & SIMPLE_RIGHT_REDIRECT)
// 			ft_putendl(">");
// 		ptr = ptr->next;
// 	}
// }

static void	print_tree(t_ast *tree, int color)
{
	if (!tree)
		return ;
	// if (tree->cmd1)
	// {
	// 	ft_putendlcol("CMD1", YELLOW);
	// 	print_cmd(tree->cmd1);
	// }
	// if (tree->cmd2)
	// {
	// 	ft_putendlcol("CMD2", YELLOW);
	// 	print_cmd(tree->cmd2);
	// }
	ft_putstr(color == 1? YELLOW : CYAN);
	ft_putstr(tree->str);
	ft_putendl(COLOR_RESET);
	print_tree(tree->left, 1);
	print_tree(tree->right, 0);
}

t_ast		*line_to_ast(char *line)
{
	t_ast	*tree;

	tree = NULL;
	if (!(tree = ast_create_tree(line)))
		return (NULL);
	if (!ast_parse_tree(tree))
	{
		ast_destroy_tree(tree);
		return (NULL);
	}
	if (!ast_to_cmdwr(&tree))
		return (NULL);
	print_tree(tree, 1);
	return (tree);
}
