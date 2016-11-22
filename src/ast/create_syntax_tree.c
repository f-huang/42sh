/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_syntax_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:43:49 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/22 23:08:16 by FannyHuang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static t_ast	*get_root(t_ast *lst_tokens)
{
	t_ast	*elem;
	t_ast	*root;
	_Bool	found;

	found = false;
	root = NULL;
	elem = lst_tokens;
	while ((elem = ast_search_for_operator(elem, AND_OR, true)))
	{
		root = elem;
		elem = elem->right.tree;
		found = true;
	}
	if (found == false)
	{
		elem = lst_tokens;
		while ((elem = ast_search_for_operator(elem, PIPE, true)))
		{
			root = elem;
			elem = elem->right.tree;
		}
	}
	return (root);
}

static t_ast	*get_leaves(t_ast **root, _Bool right)
{
	t_ast	*elem;
	t_ast	*tmp;

	if (*root == NULL)
		return (NULL);
	tmp = (*root)->left.tree;
	if ((elem = ast_search_for_operator((*root)->left.tree, AND_OR, 0)))
	{
		if (right == true)
			return (NULL);
		(*root)->left.tree = get_leaves(&elem->left.tree, 0);
		(*root)->right.tree = get_leaves(&elem->right.tree, 1);
		return (elem);
	}
	if ((elem = ast_search_for_operator((*root)->left.tree, PIPE, 0)))
	{
		(*root)->left.tree = get_leaves(&elem->left.tree, 0);
		if ((*root)->left.tree)
			(*root)->left.tree->right.tree = NULL;
		return (elem);
	}
	else
	{
		return (tmp);
	}
}

int		ast_list_to_tree(t_ast **lst_tokens)
{
	t_ast	*root;

	root = get_root(*lst_tokens);

	ft_putendlcol(root->str, GREEN);
	root->left.tree = get_leaves(&root, false);
	ft_putendlcol(root->left.tree->str, MAGENTA);
	if (root->left.tree->left.tree)
		ft_putendlcol(root->left.tree->left.tree->str, GREEN);
	if (root->left.tree->right.tree)
		ft_putendlcol(root->left.tree->right.tree->str, GREEN);
	printf("%p\n", root->left.tree->right.tree->right.tree);
	// relink_leaves(&(*lst_tokens)->left, false, change_link_left);
	return (0);
}
