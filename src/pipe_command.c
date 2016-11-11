/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:57:27 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/11 20:03:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "ft_42sh.h"
#include "libft.h"

int			pipe_command(void)
{
	pid_t	child;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putendlcol("Pipe", RED);
		return (ERROR);
	}
	if ((child = fork()) == -1)
	{
		ft_putendlcol("Fork", RED);
		return (ERROR);
	}
	else if (child == 0)
	{
		ft_putendlcol("Kiddo closes fd[1]", GREEN);
		close(fd[1]);

		char	buffer[1024 + 1];

		ft_bzero(buffer, 1024 + 1);
		read(fd[0], buffer, 1024);
		close(fd[0]);
		ft_putendlcol(buffer, MAGENTA);
	}
	else // Pere
	{
		ft_putendlcol("Daddy closes fd[0]", YELLOW);
		close(fd[0]);

		write(fd[1], "Trololol", ft_strlen("Trololol"));
		close(fd[1]);
	}
	return (GOOD);
}
