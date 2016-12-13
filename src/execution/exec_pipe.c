/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:01:52 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/12 19:15:07 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "execution.h"
#include "ast.h"

void		exec_pipe(t_shell *sh, t_ast *ast)
{
	pid_t	id;
	int		pipefd[2];
	int		tmp;
	int		first;

	first = sh->first_pipe;
	if (sh->first_pipe)
		sh->first_pipe = 0;
	pipe(pipefd);
	if ((id = fork()) > 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		if (first)
			waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		if (ast->cmd2)
			exit(exec_redirection(sh, ast->cmd2));
		else if (ast->cmd1)
			exit(exec_redirection(sh, ast->cmd1));
	}
	else if (id == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		if (ast->left)
			exit(exec_ast(sh, ast->left));
		else if (ast->cmd1)
			exit(exec_redirection(sh, ast->cmd1));
	}
}
