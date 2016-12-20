/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:41:46 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/15 15:46:15 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_read.h"
#include "libft.h"
#include "ft_42sh.h"
#include "tools.h"
#include <unistd.h>
#include <fcntl.h>

int		read_input(t_shell *sh, t_read tools, char **line)
{
	int		fd;
	int		ret;

	fd = tools.option & OPTION_U ? tools.fd : 0;
	ret = 0;
	if (!(tools.option & OPTION_D) &&\
		!(tools.option & OPTION_S) && !(tools.option & OPTION_N))
	{
		if (tools.option & OPTION_P)
			ft_putstr(tools.prompt);
		if ((ret = tl_get_next_line(fd, line)) == -1)
		{
			ft_putstr_fd("42sh : read: ", 2);
			ft_putnbr_fd(tools.fd, 2);
			ft_putstr_fd(": invalid file descriptor: Bad file descriptor\n", 2);
			return (ERROR);
		}
	}
	else
	{
	}
	(void)sh;
	return (ret == 0 ? ERROR : GOOD);
}
