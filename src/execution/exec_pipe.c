/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:01:52 by yfuks             #+#    #+#             */
/*   Updated: 2017/01/09 13:24:55 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "execution.h"
#include "ast.h"
#include "libft.h"
#include "tools.h"

static t_list	*ast_to_list(t_ast **ast)
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
				ft_lstadd(&begin, tl_lstnew(cursor->cmd2,
											sizeof(cursor->cmd2)));
		}
		if (!begin)
			begin = tl_lstnew(cursor->cmd1, sizeof(cursor->cmd1));
		else
			ft_lstadd(&begin, tl_lstnew(cursor->cmd1, sizeof(cursor->cmd1)));
		cursor = cursor->left;
	}
	return (begin);
}

static void		free_list(t_list **begin)
{
	t_list	*cursor;
	t_list	*tofree;

	cursor = *begin;
	while (cursor)
	{
		tofree = cursor;
		cursor = cursor->next;
		free(tofree);
	}
}

void			exec_pipe(t_shell *sh, t_ast **ast)
{
	pid_t	id;
	int		pipefd[2];
	int		fd_in;
	t_list	*cursor;
	t_list	*begin;
	int		tmp;

	begin = ast_to_list(ast);
	cursor = begin;
	fd_in = 0;
	while (cursor)
	{
		pipe(pipefd);
		id = fork();
		if (id > 0)
		{
			close(pipefd[1]);
			fd_in = pipefd[0];
			if (!cursor->next)
			{
				waitpid(id, &tmp, WUNTRACED | WCONTINUED);
				sh->last_return = get_command_status_code(tmp);
				free_list(&begin);
				exit(sh->last_return);
			}
			else
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
}
