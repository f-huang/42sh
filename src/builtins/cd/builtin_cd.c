/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:49:16 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/13 14:44:00 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "ft_42sh.h"
#include "environment.h"
#include "builtins.h"
#include "libft.h"
#include "tools.h"

/*
**			This function change the working directory of the current shell
**			execution environment.
**			cd -P -> Do not follow symbolic links
**				(ex: PWD=/private/tmp)
**			cd -L -> Follow symbolic links  >>>>> DEFAULT
**				(ex: PWD=/tmp)
*/

static void	set_pwd(t_variable **lst_env, char *path, _Bool follow_sl)
{
	struct stat	buf;
	char		*tmp;

	if ((tmp = sh_getenv(*lst_env, "PWD")))
		sh_setenv(lst_env, "OLDPWD", tmp);
	tmp = NULL;
	lstat(path, &buf);
	if (follow_sl == 0 || S_ISLNK(buf.st_mode) != 1)
	{
		if ((tmp = getcwd(tmp, _POSIX_PATH_MAX)))
		{
			sh_setenv(lst_env, "PWD", tmp);
			ft_strdel(&tmp);
		}
	}
	else
		sh_setenv(lst_env, "PWD", path);
}

static int	change_directory(t_variable **lst_env, char *path, _Bool follow_sl, \
		int alloc)
{
	struct stat	buf;

	if (!path)
		return (1);
	if (access(path, F_OK) == -1)
		return (cd_error(3, path));
	stat(path, &buf);
	if (S_ISDIR(buf.st_mode) != 1)
		return (cd_error(4, path));
	if (access(path, X_OK) == -1)
		return (cd_error(5, path));
	if (chdir(path) == -1)
		return (1);
	set_pwd(lst_env, path, follow_sl);
	if (alloc)
		ft_strdel(&path);
	return (0);
}

static void	append_one_dir(char **path, char *wanted)
{
	char	*tmp;

	tmp = (*path)[1] ? ft_strjoin(*path, "/") : ft_strdup(*path);
	*path ? free(*path) : 0;
	*path = ft_strjoin(tmp, wanted);
	tmp ? ft_strdel(&tmp) : 0;
}

static int	gear(char **path, char *tmp)
{
	char	*p;
	char	*cpy;

	cpy = *path;
	if (ft_strequ(tmp, "."))
		;
	else if (ft_strequ(tmp, ".."))
	{
		if ((p = ft_strrchr(cpy, '/')))
			while (*p)
			{
				if (p == *path)
					++p;
				*p = '\0';
				++p;
			}
	}
	else
		append_one_dir(path, tmp);
	return (GOOD);
}

static char	*build_path(t_variable *lst_env, char *wanted)
{
	char	*path;
	char	**tmp;
	int		i;

	if (wanted[0] != '/')
	{
		if (!(path = sh_getenv(lst_env, "PWD")))
			path = getcwd(NULL, _POSIX_PATH_MAX);
		else if (!(path = ft_strdup(path)))
			return (NULL);
		if (!(tmp = ft_strsplit(wanted, '/')))
			return (NULL);
		if (tl_arrlen(tmp) == 0 && ft_strequ(wanted, "/"))
			return (ft_strdup(wanted));
		i = 0;
		while (tmp[i])
		{
			gear(&path, tmp[i]);
			++i;
		}
		tl_freedoubletab(tmp);
	}
	else
		path = ft_strdup(wanted);
	return (path);
}

int			builtin_cd(t_shell *sh, int ac, char **av)
{
	char	*path;
	_Bool	follow_sl;
	int		i;
	int		alloc;

	i = 1;
	follow_sl = get_options(av, &i);
	path = NULL;
	alloc = 0;
	ft_putendl(av[i]);//
	if (!av[i])
	{
		if (!(path = sh_getenv(sh->lst_env, "HOME")))
			return (cd_error(1, NULL));
	}
	else if (ac - i == 1)
	{
		if (ft_strequ(av[i], "-"))
		{
			if (!(path = sh_getenv(sh->lst_env, "OLDPWD")))
				return (cd_error(2, NULL));
		}
		else
		{
			path = build_path(sh->lst_env, av[i]);
			alloc = 1;
		}
	}
	else
		return (cd_error(0, NULL));
	return (change_directory(&sh->lst_env, path, follow_sl, alloc));
}
