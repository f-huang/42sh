/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completionbis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:35:41 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/10 16:29:59 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		applylink(struct dirent *lu, char *pattern)
{
	int		p;
	char	*str;

	p = 0;
	if (match(lu->d_name, pattern) && ft_strcmp(lu->d_name, ".") &&
			ft_strcmp(lu->d_name, ".."))
	{
		str = strdup_input(lu->d_name);
		while (cor()->x > 0 && ft_getlast(*command()) != '/' &&
				!ft_isspace(ft_getlast(*command())))
			stremove();
		while (str[p])
			manage_command(str[p++]);
		ft_strdel(&str);
		return (1);
	}
	return (0);
}

int		applycommand(struct dirent *lu, char *pattern)
{
	int		p;
	char	*str;

	p = 0;
	if ((lu->d_name[0] != '.' || ft_strcmp(pattern, "*")) && (*command())[0] &&
			ft_strcmp(lu->d_name, ".") && ft_strcmp(lu->d_name, "..") &&
			match(lu->d_name, pattern))
	{
		str = strdup_input(lu->d_name);
		while (cor()->x > 0 && !ft_isspace(ft_getlast(*command())))
			stremove();
		while (str[p])
			manage_command(str[p++]);
		ft_strdel(&str);
		return (1);
	}
	return (0);
}

void	linkcase(char *pattern, char *to_open)
{
	int				i;
	DIR				*dir;
	struct dirent	*lu;

	i = ft_strlen(to_open);
	while (to_open[i] != '/')
		i--;
	to_open[i + 1] = 0;
	if (!(dir = opendir(to_open)))
		return ;
	while ((lu = readdir(dir)))
		if ((lu->d_name[0] != '.' || ft_strcmp(pattern, "*")) &&
				applylink(lu, pattern))
			break ;
	closedir(dir);
}

void	commandcase(char *pattern)
{
	t_comp	p;

	p.path = ft_getenv("PATH") ? ft_getenv("PATH") : NULL;
	p.splitted_path = p.path ? ft_strsplit(p.path, ':') : NULL;
	p.t = 0;
	while (p.splitted_path && p.splitted_path[p.t])
	{
		if (!(p.dir = opendir(p.splitted_path[p.t])))
			return ;
		while ((p.lu = readdir(p.dir)))
		{
			p.check = applycommand(p.lu, pattern);
			if (p.check)
				break ;
		}
		closedir(p.dir);
		if (p.check)
			break ;
		p.t++;
	}
	ft_tabdel(&p.splitted_path);
}

void	lastcase(char *pattern)
{
	DIR				*dir;
	struct dirent	*lu;
	int				p;
	char			*str;

	p = 0;
	dir = opendir(".");
	while ((lu = readdir(dir)))
	{
		if ((lu->d_name[0] != '.' || ft_strcmp(pattern, "*")) &&
				ft_strcmp(lu->d_name, ".") && ft_strcmp(lu->d_name, "..") &&
				match(lu->d_name, pattern))
		{
			str = strdup_input(lu->d_name);
			while (cor()->x > 0 && !ft_isspace(ft_getlast(*command())))
				stremove();
			while (str[p])
				manage_command(str[p++]);
			ft_strdel(&str);
			closedir(dir);
			return ;
		}
	}
	closedir(dir);
}
