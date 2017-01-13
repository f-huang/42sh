/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:49:16 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/13 12:59:10 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
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
	char		*new_path;
	char		**new_split;
	size_t		i;

	i = 0;
	if (wanted && ft_strequ(wanted, "-"))
		return (ft_strdup(sh_getenv(env, "OLDPWD")));
	if (ft_strequ(wanted, "~"))
//		return (ft_strdup(!(new_path = sh_getenv(env, "HOME")) ? \
//					getpwuid(getuid())->pw_dir : new_path));
	{
		if (!(sh_getenv(env, "HOME")))
			return (ft_strdup(getpwuid(getuid())->pw_dir));
		else
			return (ft_strdup(sh_getenv(env, "HOME")));
	}
	if (!(new_split = ft_strsplit(wanted, '/')))
		return (NULL);
	if (!(new_path = ft_strdup(current_path)))
	{
		tl_freedoubletab(new_split);
		return (NULL);
	}
	if (wanted[0] == '/')
		while (i++ < tl_arrlen(new_split))
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
	char	*pwd;
	int		r;

	(void)ac;
	pwd = NULL;
	if (!(current_path = sh_getenv(sh->lst_env, "PWD")))
		pwd = getcwd(NULL, _POSIX_PATH_MAX);
	if (!(final_path = (av[1] && !ft_strcmp(av[1], "/")) ? ft_strdup("/") :
	build_path(av[1], pwd ? pwd : current_path, sh->lst_env)))//ajout option -P
		return (ERROR);
	if ((r = chdir(final_path) != -1))
	{
		sh_setenv(&sh->lst_env, "OLDPWD", current_path);
		sh_setenv(&sh->lst_env, "PWD", final_path);
	}
	else
		cd_error(r, av[1]);
	if (pwd)
		ft_strdel(&pwd);
	ft_strdel(&final_path);
	return (GOOD);
}
