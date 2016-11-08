#include "builtin_env.h"
#include "libft.h"

int			main(int ac, char **av, char **env)
{
	char	**internal_env;

	if (ac < 2)
		return (env_print_env(env));
	internal_env = env_copy_env(env);
	return (env_parse_argv(ac, av, &internal_env));
}
