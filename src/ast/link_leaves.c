/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_leaves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 11:17:12 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/24 17:43:11 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static const int	g_operator[] = {AND, OR, PIPE};

static void		debug_print_tree(t_ast *list, int color)
{
	if (!list)
		return;
	ft_putendlcol(list->str, color == 1 ? YELLOW : MAGENTA);
	debug_print_tree(list->left, 1);
	debug_print_tree(list->right, 0);
}

static t_ast	*get_last_link(t_ast *list)
{
	t_ast	*last;

	last = list;
	while (last->right)
		last = last->right;
	return (last);
}

static t_ast	*get_root(t_ast *list)
{
	t_ast	*root;
	t_ast	*ptr;
	int		i;

	ptr = get_last_link(list);
	i = -1;
	while (++i < 3)
	{
		if ((root = ast_search_for_operator(ptr, g_operator[i], false)))
			return (root);
	}
	return (NULL);
}

static t_ast	*operator_found(t_ast *ptr, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	ft_putendlcol(ptr->str, GREEN);
	if (ptr->cmd1 == NULL)
		left = left_branch(&ptr, i);
	if (ptr->cmd2 == NULL)
		right = right_branch(&ptr, i);
	if (!left)// || (left && left->operator == COMMAND))
		ptr->left = NULL;
	if (!right)// || (right && right->operator == COMMAND))
		ptr->right = NULL;
	return (ptr);
}

static t_ast	*left_branch(t_ast **list, int *i)
{
	t_ast	*ptr;

	if (*list == NULL || *i == 3)
		return (NULL);
	ft_printf("^MAGENTA^->%i -- root : %s^EOC^\n", *i, (*list)->str);
	if ((ptr = ast_search_for_operator((*list)->left, g_operator[*i], false)))
	{
		return ((*list)->left = operator_found(ptr, i));
	}

	return (NULL);
}
static t_ast	*search_operator_right_branch(t_ast *list, int what)
{
	t_ast	*ptr;

	ptr = list;
	while (ptr)
	{
		if (ptr->operator == what)
			return (ptr);
		else if (ptr->operator < what)
			return (NULL);
		ptr = ptr->right;
	}
	return (NULL);
}

static t_ast	*right_branch(t_ast **list, int *i)
{
	t_ast	*ptr;

	if (*list == NULL || *i == 3)
		return (NULL);
		ft_printf("^CYAN^->%i -- root : %s^EOC^\n", *i, (*list)->str);

	if ((ptr = search_operator_right_branch((*list)->right, g_operator[*i])))
	{
		return ((*list)->right = operator_found(ptr, i));
	}
	return (NULL);

}

t_ast	*ast_link_leaves(t_ast **list)
{
	int		i;

	i = 0;
	*list = get_root(*list);
	ft_printf("^GREEN^%s^EOC^\n", (*list)->str);
	left_branch(list, &i);

	i = 1;
	right_branch(list, &i);
	return (NULL);
}
