/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_with_cmdwr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:32:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/23 19:29:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static	t_redirections	parse_redir_str(t_redirections *redir, char *str)
{
	int		i;

	//Parse str -> fill struct
	//Push_back (list, new_redir);
}

static t_redirections	*fill_redirection_struct(t_ast **list)
{
	t_redirections	*redir;
	t_ast			*ptr;
	int				i;

	redir = NULL;
	ptr = *list;
	while (ptr && ptr->operator == REDIRECTION)
	{
		parse_redir_str(&redir, ptr->str);
		ptr = ptr->next;
	}
	return (redir);
}

static t_cmdwr	*create_cmdwr(t_ast **list)
{
	t_cmdwr			*cmd;

	cmd = NULL;
	if (!(cmd = (t_cmdwr*)ft_memalloc(sizeof(t_cmdwr))))
		return (NULL);
	if ((*list)->next && (*list)->next->operator == REDIRECTION)
	{
		cmd->redir = fill_redirection_struct(&(*list)->next)
	}
}

t_ast	*create_tree_with_cmdwr(t_ast *list)
{
	t_ast	*tree;
	t_cmdwr	*cmd;

	while (list)
	{
		if (list->operator == COMMAND)
		{
			cmd = create_cmdwr(&list);
			//link_cmdwr;
		}
		// else if (list->operator == REDIRECTION)
			//fill_redirection(&cmd);
		list = list->right;
	}
}
