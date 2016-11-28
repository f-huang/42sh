/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:57:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/12 17:04:12 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "ft_42sh.h"
#include "libft.h"

//fd[0] -> Sortie tube STDIN-> READ		-> Right side ?
//fd[1] -> Entree tube STDOUT-> WRITE	-> Left side ?

int			test(int pipefd[2])
{
	char	*cmd1[] = {"echo", "TROLOLOL", NULL};
	char	*cmd2[] = {"wc", "-c", NULL};
	pid_t	child2;

	if ((child2 = fork()) == -1)
	{
		ft_putendlcol("Fork2", RED);
		return (ERROR);
	}
	else if (child2 == 0 )
	{
		ft_putendlcol("Kiddo closes fd[0]", GREEN);

		dup2(pipefd[0], 0);	/* tube to Stdin */
		close(pipefd[1]);	/* Doesnt STDOUT */

		ft_putendlcol("WC", GREEN);
		execve("/usr/bin/wc", cmd2, NULL);
	}
	else
	{
		ft_putendlcol("Daddy closes fd[1]", YELLOW);

		dup2(pipefd[1], 1); /*stdout to tube */
		close(pipefd[0]);	/* Doesnt need STDIN */

		execve("/bin/echo", cmd1, NULL);
	}
	return (GOOD);
}

int			pipe_command(void)
{
	pid_t	child1;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		ft_putendlcol("Pipe", RED);
		return (ERROR);
	}
	if ((child1 = fork()) == -1)
	{
		ft_putendlcol("Fork1", RED);
		return (ERROR);
	}
	else if (child1 == 0)// LEFT
	{
		if (test(pipefd))
			ft_putendlcol("Pipe good", GREEN);
		exit(1);
	}
	else
	{
		int		status;
		while ((child1 = wait(&status)) != -1)
			printf("process %d exits with %d\n", child1, WEXITSTATUS(status));
	}
	return (GOOD);
}
