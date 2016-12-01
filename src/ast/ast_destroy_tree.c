/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destroy_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:05:13 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/01 12:25:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

void	ast_destroy_tree(t_ast *tree)
{
	if (!tree)
		return ;
	ast_destroy_tree(tree->left);
	ast_destroy_tree(tree->right);
	tree->operator = 0;
	ft_strdel(&tree->str);
	if (tree->cmd1)
		ast_free_cmdwr(&tree->cmd1);
	if (tree->cmd2)
		ast_free_cmdwr(&tree->cmd2);
	ft_memdel((void*)&tree);
}
