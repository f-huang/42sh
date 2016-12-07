/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:20:49 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/07 15:42:03 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ast.h"
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "substitution.h"

static	int	exec_and(t_shell *sh, t_ast *ast)
{
	pid_t	id;
	int		tmp;

	id = fork();
	if (id > 0) // father
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		sh->last_return = get_command_status_code(tmp);
		if (sh->last_return == 0 && ast->right)
			exec_ast(sh, ast->right);
		else if (sh->last_return == 0 && ast->cmd2)
			exec_redirection(sh, ast->cmd2);
		else if (sh->last_return == 0 && ast->cmd1)
			exec_redirection(sh, ast->cmd1);
		return (sh->last_return);
	}
	else if (id == 0) // son
	{
		if (ast->left)
			exit(exec_ast(sh, ast->left));
		else
			exit(exec_redirection(sh, ast->cmd1));
	}
	return (0);
}

static	int	exec_or(t_shell *sh, t_ast *ast)
{
	pid_t	id;
	int		tmp;

	id = fork();
	if (id > 0) // father
	{
		waitpid(0, &tmp, WUNTRACED | WCONTINUED);
		sh->last_return = get_command_status_code(tmp);
		if (sh->last_return != 0 && ast->right)
			exec_ast(sh, ast->right);
		else if (sh->last_return != 0 && ast->cmd2)
			exec_redirection(sh, ast->cmd2);
		else if (sh->last_return != 0 && ast->cmd1)
			exec_redirection(sh, ast->cmd1);
		return (sh->last_return);
	}
	else if (id == 0) // son
	{
		if (ast->left)
			exit(exec_ast(sh, ast->left));
		else
			exit(exec_redirection(sh, ast->cmd1));
	}
	return (0);
}

int			exec_pipes(t_shell *sh, t_ast *ast)
{
	pid_t	id;
	pid_t	child;
	int		pipefd[2];
	int		tmp;

	id = fork();
	if (id > 0)
	{
		waitpid(0, &tmp, 0);
		sh->last_return = get_command_status_code(tmp);
		return (sh->last_return);
	}
	else if (id == 0)
	{
		pipe(pipefd);
		child = fork();
		if (child > 0)
		{
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			if (ast->cmd2)
				exit(exec_redirection(sh, ast->cmd2));
			else if (ast->cmd1)
				exit(exec_redirection(sh, ast->cmd1));
		}
		else if (child == 0)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			if (ast->left)
				exit(exec_ast(sh, ast->left));
			else if (ast->cmd1)
				exit(exec_redirection(sh, ast->cmd1));
		}
	}
	return (0);
}

int			exec_ast(t_shell *sh, t_ast *ast)
{
	if (ast->operator == AND)
		return (exec_and(sh, ast));
	if (ast->operator == OR)
		return (exec_or(sh, ast));
	if (ast->operator == COMMAND || ast->operator == REDIRECTION)
		return (exec_redirection(sh, ast->cmd1));
	if (ast->operator == PIPE)
		return (exec_pipes(sh, ast));
	return (0);
}
