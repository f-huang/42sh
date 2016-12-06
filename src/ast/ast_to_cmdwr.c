/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmdwr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:32:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/06 11:43:42 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "ft_42sh.h"

static void		link_cmdwr(t_ast **ptr, t_cmdwr **cmd)
{
	if ((*ptr)->cmd1 == NULL)
		(*ptr)->cmd1 = *cmd;
	else
		(*ptr)->cmd2 = *cmd;
}

int				ast_to_cmdwr(t_ast **root)
{
	t_cmdwr	*cmd;
	t_ast	*ptr;
	t_ast	*ptr2;

	ptr = *root;
	ptr2 = NULL;
	if (!ptr)
		return (GOOD);
	ft_putendlcol(ptr->str, RED);
	if (ptr->left)
		ft_putnbrendl(ptr->left->operator);
	if (ptr->right)
		ft_putnbrendl(ptr->right->operator);
	if ((ptr->operator == COMMAND && (ptr2 = ptr)) ||\
		(ptr->left && ptr->left->operator == COMMAND && (ptr2 = ptr->left)) ||\
		(ptr->right && ptr->right->operator == COMMAND && (ptr2 = ptr->right)))
	{
		cmd = NULL;
		if (!(cmd = (t_cmdwr*)ft_memalloc(sizeof(t_cmdwr))))
			return (ERROR);
		cmd->command = NULL;
		cmd->redirs = NULL;
		if (!cmdwr_fill_struct(&cmd, ptr2->str))
		{
			ast_free_cmdwr(&cmd);
			return (ERROR);
		}
		if (cmd->redirs != NULL)
			ptr2->operator = REDIRECTION;
		link_cmdwr(&ptr, &cmd);
		if (ptr->operator != COMMAND)
		{
			ft_putendlcol(ptr2->str, MAGENTA);
			ast_remove_link(root, ptr2);
		}
	}
	ast_to_cmdwr(&(ptr)->left);
	ast_to_cmdwr(&(ptr)->right);
	return (GOOD);
}
