/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmdwr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:32:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/29 21:43:14 by fhuang           ###   ########.fr       */
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

	ptr = *root;
	if (!ptr)
		return (GOOD);
	if ((ptr)->operator == COMMAND)
	{
		cmd = NULL;
		if (!(cmd = (t_cmdwr*)ft_memalloc(sizeof(t_cmdwr))))
			return (ERROR);
		if (!cmdwr_fill_struct(&cmd, (ptr)->str))
			return (ERROR);
		if (cmd->redirs != NULL)
			(ptr)->operator = REDIRECTION;
		link_cmdwr(root, &cmd);
		if ((ptr)->right)
			ast_remove_link(root, (ptr));
	}
	ast_to_cmdwr(&(ptr)->left);
	ast_to_cmdwr(&(ptr)->right);
	return (GOOD);
}
