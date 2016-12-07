/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:49:16 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/07 15:14:13 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "ft_42sh.h"
#include "environment.h"
#include "builtins.h"
#include "libft.h"

/*
**			This function change the working directory of the current shell
**			execution environment.
**			cd -P -> Do not follow symbolic links
**				(ex: PWD=/private/tmp)
**			cd -L -> Follow symbolic links  >>>>> DEFAULT
**				(ex: PWD=/tmp)
*/

static int	cd_error(int index, char *path)
{
	const char	*error_msg[] = {
		"Too many arguments.\n",
		"'HOME' variable not set.\n",
		"'OLDPWD' variable not set.\n",
		": No such file or directory.\n",
		": Not a directory.\n",
		": Permission denied.\n",
		NULL
	};
	ft_putstr_fd("cd : ", 2);
	if (index > 2 && index < 6 && path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(error_msg[index], 2);
	return (1);
}


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

static int	change_directory(t_variable **lst_env, char *path, _Bool follow_sl)
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
	return (0);
}

int			builtin_cd(t_shell *sh, int ac, char **av)
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
}
