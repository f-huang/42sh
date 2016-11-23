/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_syntax_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:43:49 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/23 19:29:28 by fhuang           ###   ########.fr       */
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

static void		set_null(t_ast **ptr)
{
	ft_printf("  ptr: %s\n", (*ptr)->str);
	(*ptr)->right = NULL;
	(*ptr)->left = NULL;
}

static t_ast	*get_leaves(t_ast **root, _Bool right, int *i)
{
	t_ast	*elem;
	t_ast	*tmp;

	if (*root == NULL)
		return (NULL);
	tmp = right ? (*root)->right : (*root)->left;
	if ((elem = ast_search_for_operator(right ? (*root)->right : (*root)->left, AND_OR, right)))
	{
		ft_putendlcol(elem->str, CYAN);
		if (right == true)
		{
			ft_putstr(right ? "right" : "left");
			set_null(tmp ? &tmp : root);
			return (tmp);
		}
		(*root)->right = get_leaves(&elem, 1, i);
		(*root)->left = get_leaves(&elem, 0, i);
		return (elem);
	}
	if ((elem = ast_search_for_operator(right ? (*root)->right : (*root)->left, PIPE, right)))
	{
		// (*root)->right = get_leaves(&elem, 1, i);
		(*root)->left = get_leaves(&elem, 0, i);
		return (elem);
	}
	else
	{
		ft_putstr(right ? "right" : "left");
		set_null(tmp ? &tmp : root);
		return (tmp);
	}
}

t_ast		*ast_list_to_tree(t_ast **lst_tokens)
{
	t_ast	*root;
	int		i = 0;

	root = get_root(*lst_tokens);
	root->right = get_leaves(&root, true, &i);
	i = 0;
	root->left = get_leaves(&root, false, &i);
	return (root);
}
