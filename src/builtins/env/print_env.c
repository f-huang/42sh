#include "libft.h"

int		env_print_env(char **env)
{
	int		i;

	i = 0;
	if (env == 0)
		return (0);
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
	return (0);
}
