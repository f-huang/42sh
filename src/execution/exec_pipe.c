/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:54:32 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/23 15:40:03 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"

int		exec_pipes(t_shell *sh)
{
	pid_t	id;
	char	*cmd1[] = {"echo", "TROLOLOL", NULL};
	char	*cmd2[] = {"wc", "-c", NULL};
	int		pipefd[2];

	pipe(pipefd);
	id = fork();
	if (id > 0)
	{
		dup2(pipefd[1], 1); /*stdout to tube */
 		close(pipefd[0]);	/* Doesnt need STDIN */
		exit(exec_command(sh, cmd1));
//		execve("/bin/echo", cmd1, NULL);
	}
	else if (id == 0)
	{
		dup2(pipefd[0], 0);	/* tube to Stdin */
		close(pipefd[1]);	/* Doesnt STDOUT */
		exit(exec_command(sh, cmd2));
// 		execve("/usr/bin/wc", cmd2, NULL);
	}
 	return (GOOD);
}
