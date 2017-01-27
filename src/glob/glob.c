/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoac <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 15:58:56 by tpoac             #+#    #+#             */
/*   Updated: 2017/01/26 18:27:19 by tpoac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

static char			*handle_dir(char *s, DIR **current_dir)
{
	char			*dir;
	int				end;
	int				stat;

	dir = ".";
	stat = 0;
	if (ft_strchr(s, '/'))
	{
		end = tl_strnupto(s, "/", tl_strcntc(s, "/") - 1);
		dir = ft_strsub(s, 0, end);
		if (!(*current_dir = opendir(dir)))
			stat = 1;
	}
	else
	{
		if (!(*current_dir = opendir(".")))
			stat = 2;
	}
	if (stat > 0)
	{
		ft_strequ(dir, ".") ? 0 : free(dir);
		return (NULL);
	}
	return (dir);
}

static void			ft_glob_files(
					char *s,
					char *d_name,
					t_list **files,
					char *change_dir)
{
	t_list			*new;
	char			*tmp;
	int				begin;

	begin = tl_strnupto(s, "/", tl_strcntc(s, "/") - 1);
	if (d_name[0] != '.' && matchpp(d_name, &s[begin]))
	{
		new = ft_lstnew(d_name, ft_strlen(d_name) + 1);
		if (!ft_strequ(change_dir, "."))
		{
			tmp = change_dir;
			new->content = ft_strjoin(change_dir, new->content);
			free(tmp);
		}
		ft_lstaddend(files, new);
	}
}

t_list				*ft_glob(char *s)
{
	DIR				*current_dir;
	struct dirent	*dir;
	t_list			*files;
	char			*change_dir;

	if (!s)
		return (NULL);
	dir = NULL;
	files = NULL;
	current_dir = NULL;
	change_dir = handle_dir(s, &current_dir);
	while ((dir = readdir(current_dir)) != NULL)
		ft_glob_files(s, dir->d_name, &files, change_dir);
	ft_strequ(change_dir, ".") ? 0 : free(change_dir);
	closedir(current_dir);
	if (!files)
		files = ft_lstnew(s, ft_strlen(s) + 1);
	return (files);
}
