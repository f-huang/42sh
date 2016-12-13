/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:01:52 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/13 16:19:52 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "execution.h"
#include "ast.h"
#include "libft.h"
#include "tools.h"

static	t_list		*ast_to_list(t_ast **ast)
{
	t_ast	*cursor;
	t_list	*begin;

	cursor = *ast;
	begin = 0;
	while (cursor)
	{
		if (cursor->cmd2)
		{
			if (!begin)
				begin = tl_lstnew(cursor->cmd2, sizeof(cursor->cmd2));
			else
				ft_lstadd(&begin, tl_lstnew(cursor->cmd2, sizeof(cursor->cmd2)));
		}
		if (!begin)
			begin = tl_lstnew(cursor->cmd1, sizeof(cursor->cmd1));
		else
			ft_lstadd(&begin, tl_lstnew(cursor->cmd1, sizeof(cursor->cmd1)));
		cursor = cursor->left;
	}
	return (begin);
}

int			exec_pipe(t_shell *sh, t_ast **ast)
{
	pid_t	id;
	int		pipefd[2];
	int		fd_in;
	t_list	*cursor;
	t_list	*begin;
	int		first;

	begin = ast_to_list(ast);
	cursor = begin;
	first = 1;
	fd_in = 0;
	while (cursor)
	{
		pipe(pipefd);
		id = fork();
		if (id > 0)
		{
			close(pipefd[1]);
			fd_in = pipefd[0];
//			if (first)
//			{
//				first = 0;
				waitpid(0, NULL, WUNTRACED | WCONTINUED);
//			}
			cursor = cursor->next;
		}
		else if (id == 0)
		{
			dup2(fd_in, 0);
			if (cursor->next)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			exit(exec_redirection(sh, (t_cmdwr *)cursor->content));
		}
	}
	return (ERROR);
}
