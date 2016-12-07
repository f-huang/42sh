/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 16:15:35 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/07 15:00:52 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"

static char	*gnl_strjoin_free(char *s1, char const *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	tmp = NULL;
	return ((char*)s1);
}

static int	update_line_lfo(char **line, char **lfo)
{
	if (*lfo)
	{
		*line = ft_strdup(*lfo);
		free(*lfo);
		*lfo = NULL;
	}
	else
		*line = (char*)ft_strnew(1);
	if (*line == NULL)
		return (-1);
	return (0);
}

int			tl_get_next_line(int fd, char **line)
{
	int				ret;
	static char		*lfo = NULL;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || BUFF_SIZE <= 0 || update_line_lfo(line, &lfo) == -1)
		return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	while ((ft_strchr(*line, '\n') == 0) && (ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		if (!(*line = gnl_strjoin_free(*line, buf)))
			return (-1);
	}
	tmp = ft_strstr(*line, "\n");
	if (tmp)
	{
		lfo = ft_strdup(tmp + 1);
		ft_bzero(tmp, ft_strlen(tmp));
	}
	if (*line && !**line)
		ft_strdel(&(*line));
	return (*line && ft_strlen(*line) ? 1 : 0);
}
