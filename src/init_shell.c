#include <limits.h>
#include <unistd.h>
#include "ft_42sh.h"
#include "tools.h"
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

static int		set_bin_path(char **bin_path, char *av_0)
{
	char	buffer[_POSIX_PATH_MAX + 1];

	if (!getcwd(buffer, _POSIX_PATH_MAX + 1))
		return (ERROR);
	ft_strclr(av_0 + ft_strlen(av_0) - 4);
	av_0 = ft_strcat(av_0, "bin/");
	if (!(*bin_path = tl_str3join(buffer,\
		buffer[ft_strlen(buffer) - 1] == '/' ? "" : "/", av_0)))
		return (ERROR);
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

int		init_shell(t_shell *sh, char *av_0)
{
	ft_bzero(sh, sizeof(t_shell));
	if (!copy_environment(&sh->lst_env))
		return (ERROR);
	if (!set_bin_path(&sh->bin_path, av_0))
		return (ERROR);
	set_default(&sh->lst_env);
	init_history(&sh->all_history);
//	if (!init_history(&sh->all_history))
//		return (ERROR);
//	if (!(init_termios(sh->term, sh->window)))
//		return (ERROR);
	return (GOOD);
}
