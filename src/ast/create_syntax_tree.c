/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_syntax_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:43:49 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/18 16:25:44 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static void		get_root(t_ast **lst_tokens)
{
	t_ast	*elem;
	_Bool	found;

	found = false;
	elem = *lst_tokens;
	while ((elem = ast_search_for_operator(elem, true, true)))
	{
		*lst_tokens = elem;
		elem = elem->right;
		found = true;
	}
	if (found == false)
	{
		elem = *lst_tokens;
		while ((elem = ast_search_for_operator(elem, false, true)))
		{
			*lst_tokens = elem;
			elem = elem->right;
		}
	}
}

static void		change_link_right(t_ast **root, t_ast *elem)
{
	if (elem)
	{
		if ((*root)->left)
			(*root)->left->right = elem;
	}
}

static void		relink_leaves(t_ast **root, _Bool right, void (*f)(t_ast**, t_ast *))
{
	t_ast	*elem;

	if (*root == NULL)
		return ;
	elem = *root;
	if ((elem = ast_search_for_operator(*root, true, right)))
		relink_leaves(right ? &elem->right : &elem->left, right, f);
	else if ((elem = ast_search_for_operator(*root, false, right)))
		relink_leaves(right ? &elem->right : &elem->left, right, f);
	f(root, elem);
}

int		ast_create_syntax_tree(t_ast **lst_tokens)
{
	get_root(lst_tokens);

	relink_leaves(&(*lst_tokens)->right, true, change_link_right);
	// relink_leaves(&(*lst_tokens)->left, false, change_link_left);
	return (0);
}
