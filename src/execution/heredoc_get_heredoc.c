/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_get_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:04:11 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/01 17:18:37 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	t_list	*get_words(char *end)
{
	char		*line;
	t_list		*words;
	t_list		*cursor;

	line = 0;
	cursor = 0;
	while (heredoc_prompt() && get_line(&line) == 1 && ft_strcmp(line, end))
	{
		if (cursor == 0)
		{
			cursor = ft_lstnew(ft_strdup(line), ft_strlen(line));
			words = cursor;
		}
		else
		{
			cursor->next = ft_lstnew(ft_strdup(line), ft_strlen(line));
			cursor = cursor->next;
		}
		ft_strclr(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (words);
}

/*
**	this function add a command line to retrieve heredoc and put the words
**	into the cmd->heredocs
*/

void		get_heredoc(t_cmdwr *cmd, t_redirections *r)
{
	t_list		*heredocs_words;
	t_heredocs	*heredocs_list;

	heredocs_list = cmd->heredocs;
	heredocs_words = get_words(r->dest);
	if (heredocs_words)
	{
		while (heredocs_list && heredocs_list->next)
			heredocs_list = heredocs_list->next;
		if (!cmd->heredocs)
			cmd->heredocs = get_new_heredocs(heredocs_words);
		else
			heredocs_list->next = get_new_heredocs(heredocs_words);
	}
}
