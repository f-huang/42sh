/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:17:47 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/28 18:37:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_42sh.h"
#include "tools.h"
#include "substitution.h"

static char		*save_home(char *s)
{
	char		*save;

	if (!(save = ft_strdup(s)))
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
	if (!(path = tl_strndup(s, (last - s))))
		return (NULL);
	dir = open_dir(path);
	while ((ent = readdir(dir)))
	{
		if (ft_strequ(p, ent->d_name))
		{
			if (!(save = tl_str3join(path, "/", p)))
				return (NULL);
			break ;
		}
	}
	close_dir(dir);
	ft_strclr(path);
	ft_strdel(&path);
	return (!save ? ft_strjoin("~", p) : save);
}

static char		*save_remain(char *s, char *p)
{
	char		*save;

	save = NULL;
	if (ft_isalpha(p[1]))
		save = save_user(s, p + 1);
	else
	{
		if (!(save = ft_strjoin(s, p + 1)))
			return (NULL);
	}
	return (save);
}

int				tilde(t_shell *sh, char **acmd)
{
	char		*save;
	int			ret;

	ret = 0;
	if (*acmd[0] == '~' && (save = sh_getenv(sh->lst_env, "HOME")))
	{
		if (ft_strlen(*acmd) == 1)
			save = save_home(save);
		else
			save = save_remain(save, *acmd);
		ft_strdel(acmd);
		*acmd = save;
	}
	return (GOOD);
}
