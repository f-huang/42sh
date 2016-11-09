#include <unistd.h>
#include <limits.h>
#include "builtin_cd.h"
#include "environment.h"

/*
**			This function change the working directory of the current shell
**			execution environment.
*/

static void	set_pwd(t_environment *lst_env)
{
	char	*tmp;

	if ((tmp = sh_getenv(lst_env, "PWD")))
		sh_setenv(lst_env, "OLDPWD", tmp);
	tmp = NULL;
	if ((tmp = getcwd(tmp, _POSIX_PATH_MAX)))
	{
		sh_setenv(lst_env, "PWD", tmp);
		ft_strdel(&tmp);
	}
}

static void	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	set_pwd(lst_env);
}

static void	go_to(t_environment *lst_env, int dest)
{
	char	*p;

	if ((p = sh_getenv(lst_env, dest ? "HOME" : "OLDPWD")))
		change_directory(p);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dest ? "HOME" : "OLDPWD", 2);
		ft_putendl_fd(" not set", 2);
	}
}

int			builtin_cd(t_shell *sh, int ac, char **av)
{
	if (ac == 1)
		go_to(lst_env, HOME);
	else if (ac == 2)
	{
		if (av[1][0] == '/' || ft_strnequ(av[1], "./", 2)\
							|| ft_strnequ(av[1], "../", 3))
			change_directory(av[1]);
		else if (ft_strequ(av[1], "-"))
			go_to(lst_env, OLDPWD);
	}
	else if (ac == 3)
	{
		// DO OPTIONS
	}
	else
		ft_putstr_fd("cd: Too many arguments", 2);
}
