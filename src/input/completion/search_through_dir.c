/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_through_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:33:33 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/24 17:04:22 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_42sh.h"
#include "libft.h"
#include "input.h"
#include "tools.h"

static void	add_in_list(char *dir_name, char *file_name)
{
	char	*path;

	path = NULL;
	if (*dir_name && dir_name[ft_strlen(dir_name) - 1] == '/')
	{
		path = ft_strjoin(dir_name, file_name);
	}
	else
	{
		path = ft_strdup(file_name);
	}
	if (tl_is_a_directory(path))
		path = tl_strmerge(path, "/");
	ft_lstadd(get_list_completion(), ft_lstnew(path, ft_strlen(path) + 1));
	ft_strdel(&path);
}

int			search_through_dir(char *dir_name, char *command)
{
	DIR			*dir;
	t_dirent	*sd;
	int			len;
	char		*trim;
	char		*tmp;

	if ((dir = opendir(*dir_name == '\0' ? "." : dir_name)) == NULL)
		return (1);
	trim = ft_strtrim(command);
	len = ft_strlen(trim);
	while ((sd = readdir(dir)))
	{
		if (ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, ".."))
			continue;
		tmp = tl_str3join(dir_name, "/", sd->d_name);
		if (ft_strnequ(sd->d_name, trim, len))
			add_in_list(dir_name, sd->d_name);
		ft_strdel(&tmp);
	}
	ft_strdel(&trim);
	return (closedir(dir) == -1 ? 1 : 0);
}
