/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_stdin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 00:24:30 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 13:06:50 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		get_next_line_stdin(int fd, char **line)
{
	char	tmp[2];
	char	*tmp2;
	int		r;

	*line = ft_strnew(1);
	while ((r = read(fd, tmp, 1)) > 0)
	{
		tmp[1] = 0;
		if (tmp[0] == '\n')
			tmp[0] = 0;
		tmp2 = *line;
		*line = ft_strjoin(*line, tmp);
		ft_strdel(&tmp2);
		if (!tmp[0])
			break ;
	}
	return (r);
}
