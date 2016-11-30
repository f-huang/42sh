/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:35:38 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/30 04:59:34 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "execution.h"
#include "ast.h"

static	t_heredocs	*getnewheredocs(t_list *words)
{
	t_heredocs	*doc;

	if (!(doc = (t_heredocs *)malloc(sizeof(t_heredocs))))
		return (0);
	doc->words = words;
	doc->next = 0;
	return (doc);
}

static	void	get_heredoc(t_shell *sh, t_cmdwr *cmd, t_redirections *r)
{
	char		*line;
	t_list		*heredocs_words;
	t_list		*cursor;
	t_heredocs	*heredocs_list;

	(void)sh;
	(void)r;
	line = 0;
	heredocs_list = cmd->heredocs;
	heredocs_words = 0;
	cursor = heredocs_words;
	while (42)
	{
		ft_putstr("heredoc de fdp> ");
		if (get_line(&line) != 1)
		{
			ft_strclr(line);
			ft_strdel(&line);
			ft_putendl("EOF");
			break ;
		}
		// fill structs
		if (cursor == 0)
		{
			cursor = ft_lstnew(ft_strdup(line), ft_strlen(line));
			heredocs_words = cursor;
		}
		else
		{
			cursor->next = ft_lstnew(ft_strdup(line), ft_strlen(line));
			cursor = cursor->next;
		}
		ft_strclr(line);
		ft_strdel(&line);
	}
	if (heredocs_words)
	{
		while (heredocs_list && heredocs_list->next)
			heredocs_list = heredocs_list->next;
		if (!cmd->heredocs)
			cmd->heredocs = getnewheredocs(heredocs_words);
		else
			heredocs_list->next = getnewheredocs(heredocs_words);
	}
}

static	int		retrieve_heredocs(t_shell *sh, t_cmdwr *cmd)
{
	t_redirections		*cursor;

	cursor = cmd->redirs;
	while (cursor)
	{
//		if (cursor->type & SIMPLE_LEFT_REDIRECT)
//			ft_putendl("c kode avc le ku (quode 2 kiquou)");
		if (cursor->type & DOUBLE_LEFT_REDIRECT)
			get_heredoc(sh, cmd, cursor);
		cursor = cursor->next;
	}
	return (GOOD);
}

static	int		get_heredocs_from_ast(t_shell *sh, t_ast *ast)
{
	if (ast->operator == COMMAND || ast->operator == REDIRECTION)
		return (retrieve_heredocs(sh, ast->cmd1));
	if (ast->right)
		get_heredocs_from_ast(sh, ast->right);
	if (ast->left)
		get_heredocs_from_ast(sh, ast->left);
	return (GOOD);
}

int		get_heredocs(t_shell *sh, t_list **list)
{
	t_list	*cursor;

	cursor = *list;
	while (cursor)
	{
		get_heredocs_from_ast(sh, cursor->content);
		cursor = cursor->next;
	}
	return (GOOD);
}
