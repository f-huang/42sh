#include "builtin_env.h"
#include "libft.h"

static	int	env_is_option_i(char *str)
{
	if (str[0] == '-' && str[1] == 'i')
		return (1);
	return (0);
}

static	int	env_is_namevalue(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] && str[i] == '=' && i > 0)
		return (1);
	return (0);
}

int		env_parse_argv(int ac, char **av, char ***env)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (env_is_option_i(av[i]) && i == 1)
			env_free_env(env);
		else if (env_is_namevalue(av[i]))
			env_set_env(av[i], env);
		else
			return (env_execute_command(*env, av, i));
		i++;
	}
	env_print_env(*env);
	return (0);
}
