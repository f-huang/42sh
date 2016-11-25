/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:17:47 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/25 18:49:52 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_42sh.h"
#include "tools.h"

static char		*save_home(char *s)
{
	char		*save;

	if (!(save = ft_strdup(s)))
		return (NULL);
	return (save);
}

static char		*save_remain(char *s, char *p)
{
	char		*save;

	if (!(save = ft_strjoin(s, p)))
		return (NULL);
	return (save);
}

static char		*save_user(char *s, char *p)
{
	char		*last;
	char		*path;
	DIR			*dir;
	t_dirent	*ent;
	char		*save;

	save = NULL;
	last = ft_strrchr(s, '/');
	if (!(path = ft_strndup(s, (last - s) + 1)))
		return (NULL);
	dir = open_dir(path);
	while ((ent = readdir(dir)))
	{
		if (ft_strequ(p, ent->d_name))
		{
			save = save_remain(path, p);
			break ;
		}
	}
	close_dir(dir);
	ft_strclr(path);
	ft_strdel(&path);
//	if (!save)
//		unknown(p);
	return (save);
}

int				tilde(t_shell *sh, char **acmd)
{
	char		*save;
	int			ret;

	ft_putendl_color(*acmd, RED);
	ret = 0;
	if ((save = sh_getenv(sh->lst_env, "HOME")))
	{
		if (!(*acmd[1]))
			save = save_home(save);
		else if (*acmd[1] == '/')
			save = save_remain(save, acmd[1]);
		else
			save = save_user(save, acmd[1]);
	}
	return (GOOD);
}
