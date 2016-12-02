/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closes_and_redirects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:38:44 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/02 18:03:08 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "execution.h"

static	void	left_redirect(t_redirections *cursor)
{
	int		fd;
    // <&- + 1<&-
	if (cursor->type & CLOSE_REDIRECT)
	{
		cursor->from_fd = (cursor->from_fd == -1) ? 0 : cursor->from_fd;
		close(cursor->from_fd);
	}
	else if (cursor->type & FILE_REDIRECT) // < toto + 1< toto
	{
		if (!exec_is_file(cursor->dest))
			exit(exec_print_command_error(NOSUCHFILE, cursor->dest));
		if (!exec_is_readable(cursor->dest))
			exit(exec_print_command_error(PERMISSIONDENIED, cursor->dest));
		cursor->from_fd = (cursor->from_fd == -1) ? 0 : cursor->from_fd;
		fd = open(cursor->dest, O_RDONLY, S_IRUSR | S_IWUSR);
		dup2(fd, cursor->from_fd);
	}
	else // <&2 + 1<&2
	{
		if (fcntl(cursor->to_fd, F_GETFD) == -1)
			exit(exec_print_command_error(BADFILEDESCRIPTOR, ft_itoa(cursor->to_fd)));
		cursor->from_fd = (cursor->from_fd == -1) ? 0 : cursor->from_fd;
		dup2(cursor->to_fd, cursor->from_fd);
	}
}

static	void	right_redirect(t_redirections *cursor)
{
	int		fd;
	// >&- + 1>&-
	if (cursor->type & CLOSE_REDIRECT)
	{
		cursor->from_fd = (cursor->from_fd == -1) ? 1 : cursor->from_fd;
		close(cursor->from_fd);		
	}
	else if (cursor->type & FILE_REDIRECT) // > toto + 1> toto
	{
		if (exec_is_file(cursor->dest) && exec_is_directory(cursor->dest))
			exit(exec_print_command_error(ISDIRECTORY, cursor->dest));
		if (exec_is_file(cursor->dest) && !exec_is_writable(cursor->dest))
			exit(exec_print_command_error(PERMISSIONDENIED, cursor->dest));
		cursor->from_fd = (cursor->from_fd == -1) ? 1 : cursor->from_fd;
		fd = open(cursor->dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd, cursor->from_fd);
	}
	else // >&2 + 1>&2
	{
		if (fcntl(cursor->to_fd, F_GETFD) == -1)
			exit(exec_print_command_error(BADFILEDESCRIPTOR, ft_itoa(cursor->to_fd)));
		cursor->from_fd = (cursor->from_fd == -1) ? 1 : cursor->from_fd;
		dup2(cursor->to_fd, cursor->from_fd);
	}
}

static	void	double_right_redirect(t_redirections *cursor)
{
	int		fd;

	if (cursor->type & FILE_REDIRECT) // >> toto + 1>> toto
	{
		if (exec_is_file(cursor->dest) && exec_is_directory(cursor->dest))
			exit(exec_print_command_error(ISDIRECTORY, cursor->dest));
		if (exec_is_file(cursor->dest) && !exec_is_writable(cursor->dest))
			exit(exec_print_command_error(PERMISSIONDENIED, cursor->dest));
		cursor->from_fd = (cursor->from_fd == -1) ? 1 : cursor->from_fd;
		fd = open(cursor->dest, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		dup2(fd, cursor->from_fd);
	}
}

static	void	redirect_heredocs(t_heredocs *cursor, t_redirections *redir)
{
	t_list		*words;
	int			fd;
	int			filed;

	fd = (redir->from_fd == -1) ? 0 : redir->from_fd;
	filed = open("/tmp/heredoc42sh", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	words = cursor->words;
	while (words)
	{
		ft_putendl_fd(words->content, filed);
		words = words->next;
	}
	close(filed);
	filed = open("/tmp/heredoc42sh", O_RDONLY, S_IRUSR | S_IWUSR);
	dup2(filed, fd);
	close(filed);
}

void	close_and_redirects(t_cmdwr *cmd, t_redirections **list)
{
	t_redirections	*cursor;
	t_heredocs		*cursaur;

	cursor = *list;
	cursaur = cmd->heredocs;
	while (cursor)
	{
		if (cursor->type & DOUBLE_LEFT_REDIRECT)
		{
			redirect_heredocs(cursaur, cursor);
			if (cursaur)
				cursaur = cursaur->next;
		}
		else if (cursor->type & SIMPLE_LEFT_REDIRECT)
			left_redirect(cursor);
		else if (cursor->type & SIMPLE_RIGHT_REDIRECT)
			right_redirect(cursor);
		else if (cursor->type & DOUBLE_RIGHT_REDIRECT)
			double_right_redirect(cursor);
		cursor = cursor->next;
	}
}
