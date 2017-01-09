/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 16:07:29 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:44:14 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

char	*ft_get_elem(int command)
{
	int				j;
	t_list			*list;

	j = 0;
	list = *ft_get_list();
	*ft_get_size() = ft_lstsize(list);
	(*ft_pos() == -1000) ? *ft_pos() = *ft_get_size() : 0;
	if (command == CODE_UP)
		*ft_pos() -= *ft_pos() > 1 ? 1 : 0;
	else
		*ft_pos() += *ft_pos() < *ft_get_size() ? 1 : 0;
	while (list && *ft_pos() >= 0 && *ft_pos() <= *ft_get_size())
	{
		if (*ft_pos() == j)
			return (ft_purify((char *)list->content, list->content_size));
		j++;
		list = list->next;
	}
	return (NULL);
}

void	ft_init_list(void)
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
		ft_lstpushback(ft_get_list(), line, ft_strlen(line) + 20);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	ft_history(char *buffer)
{
	int		fd;
	char	*path;

	path = ft_strjoin(*get_home(), "/.42sh_history");
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT);
	chmod(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_strdel(&path);
	if (buffer && buffer[0])
	{
		ft_lstpushback(ft_get_list(), buffer, ft_strlen(buffer) + 20);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	close(fd);
}
