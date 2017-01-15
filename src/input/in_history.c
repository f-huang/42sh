/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 16:07:29 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/15 19:17:56 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*ft_purify(char *str, int size)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strnew(size);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\n')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}

char	*get_elem(int command)
{
	int				j;
	t_list			*list;

	j = 0;
	list = *get_list();
	*get_size() = ft_lstsize(list);
	(*pos() == -1000) ? *pos() = *get_size() : 0;
	if (command == CODE_UP)
		*pos() -= *pos() > 1 ? 1 : 0;
	else
		*pos() += *pos() < *get_size() ? 1 : 0;
	while (list && *pos() >= 0 && *pos() <= *get_size())
	{
		if (*pos() == j)
			return (ft_purify((char *)list->content, list->content_size));
		j++;
		list = list->next;
	}
	return (NULL);
}

void	init_list(void)
{
	int		fd;
	char	*line;
	char	*path;

	path = ft_strjoin(*get_home(), "/.42sh_history");
	line = NULL;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_strdel(&path);
		return ;
	}
	ft_strdel(&path);
	while (get_next_line_stdin(fd, &line) > 0)
	{
		ft_lstpushback(get_list(), line, ft_strlen(line) + 20);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	in_history(char *buffer)
{
	int		fd;
	char	*path;

	path = ft_strjoin(*get_home(), "/.42sh_history");
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT,\
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_strdel(&path);
	if (buffer && buffer[0])
	{
		ft_lstpushback(get_list(), buffer, ft_strlen(buffer) + 20);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	close(fd);
}
