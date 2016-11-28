/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 14:33:16 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/25 18:49:55 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_42sh.h"

DIR			*open_dir(char *path)
{
	DIR		*dir;

	dir = NULL;
	if (!(dir = opendir(path)))
		return (NULL);
	return (dir);
}

int			close_dir(DIR *dir)
{
	if (closedir(dir))
		return (ERROR);
	return (GOOD);
}
