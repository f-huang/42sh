/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:49:16 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/12 16:43:39 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "ft_42sh.h"
#include "environment.h"
#include "tools.h"
#include "builtins.h"
#include "libft.h"
#include "input.h"

/*
**			This function change the working directory of the current shell
**			execution environment.
**			cd -P -> Do not follow symbolic links
**				(ex: PWD=/private/tmp)
**			cd -L -> Follow symbolic links  >>>>> DEFAULT
**				(ex: PWD=/tmp)
*/

/*
static void	set_pwd(t_variable **lst_env, char *path, _Bool follow_sl)
{
	struct stat	buf;
	char		*tmp;

	if ((tmp = sh_getenv(*lst_env, "PWD")))
		sh_setenv(lst_env, "OLDPWD", tmp);
	lstat(path, &buf);
	if (follow_sl == 0 || S_ISLNK(buf.st_mode) != 1)
	{
			if (ft_getlast(tmp) == '/')
				sh_setenv(lst_env, "PWD", &path[1]);
			else
				sh_setenv(lst_env, "PWD", path);
	}
	else
		sh_setenv(lst_env, "PWD", path);
}

static int	gear_tmp(char **path, char *tmp)
{
	char	*p;

	if (ft_strequ(tmp, "."))
		;
	else if (ft_strequ(tmp, ".."))
	{
		p = *path;
		while (*p)
			++p;
		--p;
		while (*p && *p != '/')
		{
			*p = '\0';
			--p;
		}
		if (*p == '/' && ft_strlen(*path) > 1)
			*p = '\0';
	}
	else
	{
		*path = tl_strmerge(*path, "/");
		*path = tl_strmerge(*path, tmp);
	}
	return (GOOD);
}
*/
/*static int	build_path(t_variable *lst_env, char **path)
{
	char	**tmp;
	char	*pwd;
	int		i;

	tmp = NULL;
	if (*path[0] != '/')
	{
		if (!(pwd = sh_getenv(lst_env, "PWD")))
			return (cd_error(1, NULL));
		if (!(tmp = ft_strsplit(*path, '/')))
			return (ERROR);
		if (!(*path = ft_strdup(pwd)))
			return (ERROR);
		i = 0;
		while (tmp[i])
		{
			gear_tmp(path, tmp[i]);
			++i;
		}
		tl_freedoubletab(tmp);
	}
	return (GOOD);
}*/

/*static int	change_directory(t_variable **lst_env, char *path, _Bool follow_sl)
{
	struct stat	buf;

	if (!path)
		return (1);
	build_path(*lst_env, &path);
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
	return (0);
}*/

static void		remove_one_path(char **path)
{
	int		i;

	i = 0;
	while ((*path)[i])
		i++;
	while ((*path)[i] != '/')
		i--;
	if (!i)
		(*path)[i + 1] = 0;
	else
		(*path)[i] = 0;
}

static void		append_one_path(char **path, char *wanted)
{
	char	*tmp;

	if ((*path)[1])
		tmp = ft_strjoin(*path, "/");
	else
		tmp = ft_strdup(*path);
	*path ? free(*path) : 0;
	*path = ft_strjoin(tmp, wanted);
	tmp ? free(tmp) : 0;
}

static char		*build_path(char *wanted, char *current_path, t_variable *env)
{
	char	*new_path;
	char	**new_split;
	int		i;

	i = 0;
	if (!ft_strcmp(wanted, "-"))
		return (ft_strdup(sh_getenv(env, "OLDPWD")));
	if (!wanted || !ft_strcmp(wanted, "~"))
	{
		if (!(sh_getenv(env, "HOME")))
			cd_error(1, "HOME");
		return (ft_strdup(sh_getenv(env, "HOME")));
	}
	new_split = ft_strsplit(wanted, '/');
	new_path = ft_strdup(current_path);
	if (wanted[0] == '/')
		while (i++ < 20)
			remove_one_path(&new_path);
	i = 0;
	while (new_split[i])
	{
		(!ft_strcmp(new_split[i], "..")) ? remove_one_path(&new_path) : 0;
		(ft_strcmp(new_split[i], ".") && ft_strcmp(new_split[i], "..")) ?
		append_one_path(&new_path, new_split[i]) : 0;
		i++;
	}
	tl_freedoubletab(new_split);
	return (new_path);
}

int				builtin_cd(t_shell *sh, int ac, char **av)
{
	char	*final_path;
	char	*current_path;
	int		r;

	(void)ac;
	current_path = sh_getenv(sh->lst_env, "PWD");
	final_path = (av[1] && !ft_strcmp(av[1], "/")) ? ft_strdup("/") :
	build_path(av[1], current_path, sh->lst_env);
	r = chdir(final_path);
	if (r != -1)
	{
		sh_setenv(&sh->lst_env, "OLDPWD", current_path);
		sh_setenv(&sh->lst_env, "PWD", final_path);
	}
	else
		ft_putendl("Fucking error from cd.");
	ft_strdel(&final_path);
	return (1);
}

/*int			builtin_cd(t_shell *sh, int ac, char **av)
{
	char	*path;
	_Bool	follow_sl;
	int		i;

	i = 1;
	follow_sl = get_options(av, &i);
	path = NULL;
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
			path = av[i];
	}
	else
		return (cd_error(0, NULL));
	return (change_directory(&sh->lst_env, path, follow_sl));
}*/
