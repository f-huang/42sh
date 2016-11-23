/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_syntax_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:43:49 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/23 16:11:40 by fhuang           ###   ########.fr       */
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
		elem = elem->right;
		found = true;
	}
	if (found == false)
	{
		elem = lst_tokens;
		while ((elem = ast_search_for_operator(elem, PIPE, true)))
		{
			root = elem;
			elem = elem->right;
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
	tmp = right ? (*root)->right : (*root)->left;
	if ((elem = ast_search_for_operator(right ? (*root)->right : (*root)->left, AND_OR, right)))
	{
		if (right == true)
			return (NULL);
		(*root)->left = get_leaves(&elem->left, 0);
		(*root)->right = get_leaves(&elem->right, 1);
		return (elem);
	}
	if ((elem = ast_search_for_operator(right ? (*root)->right : (*root)->left, PIPE, right)))
	{
		if (right)
			(*root)->right = get_leaves(&elem->right, 1);
		else
			(*root)->left = get_leaves(&elem->left, 0);
		return (elem);
	}
	else
	{
		if (tmp)
		{
			if (right)
				(*root)->left = NULL;
			else
				(*root)->right = NULL;
		}
		else
		{
			if (right)
				(*root)->left = NULL;
			else
				(*root)->right = NULL;
		}
		return (tmp);
	}
}

t_ast		*ast_list_to_tree(t_ast **lst_tokens)
{
	t_ast	*root;

	root = get_root(*lst_tokens);

	ft_printf("^GREEN^root : %s^EOC^\n", root->str);
	root->left = get_leaves(&root, false);
	root->right = get_leaves(&root, true);
	return (0);
}
