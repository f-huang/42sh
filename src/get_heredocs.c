/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:35:38 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/01 17:15:40 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "execution.h"
#include "ast.h"

static	int		retrieve_heredocs(t_cmdwr *cmd)
{
	t_redirections		*cursor;

	cursor = cmd->redirs;
	while (cursor)
	{
		if (cursor->type & DOUBLE_LEFT_REDIRECT)
			get_heredoc(cmd, cursor);
		cursor = cursor->next;
	}
	return (GOOD);
}

static	int		get_heredocs_from_ast(t_ast *ast)
{
	if (ast->operator == COMMAND || ast->operator == REDIRECTION)
		return (retrieve_heredocs(ast->cmd1));
	if (ast->left)
		get_heredocs_from_ast(ast->left);
	if (ast->right)
		get_heredocs_from_ast(ast->right);
	return (GOOD);
}

int		get_heredocs(t_list **list)
{
	t_list	*cursor;

	cursor = *list;
	while (cursor)
	{
		get_heredocs_from_ast(cursor->content);
		cursor = cursor->next;
	}
	return (GOOD);
}
