/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:01:52 by yfuks             #+#    #+#             */
/*   Updated: 2017/01/14 16:09:19 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "execution.h"
#include "ast.h"
#include "libft.h"
#include "tools.h"

void			exec_pipe(t_shell *sh, t_ast **ast)
{
	pid_t	id;
	int		pipefd[2];
	int		fd_in;
	t_list	*cursor;
	t_list	*begin;
	int		tmp;

	begin = ast_to_lst(ast);
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
				tl_lstfree(&begin);
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
