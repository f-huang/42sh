#include "ft_42sh.h"
#include "environment.h"

/*
**		This file is initalizing the shell. (Termios and environment).
*/

static int		copy_environment(t_environment **lst_env)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ && environ[i])
	{
		create_elem(lst_env, environ[i]);
		++i;
	}
	return (GOOD);
}

static int		increment_shlvl(t_environment **lst_env)
{
	char	*tmp;
	int		shlvl;

	if ((tmp = sh_getenv(*lst_env, "SHLVL")))
	{
		shlvl = ft_atoi(tmp);
		if (!(tmp = ft_itoa(++shlvl)))
			return (ERROR);
	}
	else if (!(tmp = ft_strdup("1")))
		return (ERROR);
	if (!sh_setenv(lst_env, "SHLVL", tmp))
		return (ERROR);
	ft_strdel(&tmp);
	return (GOOD);
}

static int		set_default(t_environment **lst_env)
{
	if (!increment_shlvl(lst_env))
		return (ERROR);
	if (!sh_getenv(*lst_env, "PATH"))
		if (!sh_setenv(lst_env, "PATH", DEFAULT_PATH))
			return (ERROR);
	return (GOOD);
}

int		init_shell(t_shell *sh)
{
	ft_bzero(sh, sizeof(t_shell));
	if (!copy_environment(&sh->lst_env))
		return (ERROR);
	set_default(&sh->lst_env);
	return (GOOD);
}
