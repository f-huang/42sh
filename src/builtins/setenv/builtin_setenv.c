#include "environment.h"
#include "libft.h"

static int	check_validity_av(char *argv)
{
	if (!ft_isalpha(*s))
	{
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
		return (ERROR);
	}
	else if (!tl_strisalnum(s))
	{
		ft_putstr_fd("setenv: ", 2);
		ft_putendl_fd("Variable name must contain alphanumeric characters.", 2);
		return (ERROR);
	}
	return (GOOD);
}

int			builtin_setenv(t_shell *sh, int ac, char **av)
{
	if (ac == 1)
		sh_print_env(sh->lst_env);
	else if ((ac == 2 || ac == 3) && check_validity_av(av[1]))
		sh_setenv(&sh->lst_env, av[1], av[2]);
	else if (ac > 3)
		ft_putendl_fd("setenv: Too many arguments.", 2);
	return (GOOD);
}

