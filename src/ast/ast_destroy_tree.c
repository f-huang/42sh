/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destroy_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:05:13 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/25 19:08:58 by fhuang           ###   ########.fr       */
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
	ft_memdel((void*)&tree);
}
