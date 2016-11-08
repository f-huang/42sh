#include "builtin_env.h"
#include "libft.h"

char	**env_copy_env(char **env)
{
	char	**new_env;
	int		env_size;
	int		i;

	env_size = env_get_env_size(env);
	if (!(new_env = env_alloc_env(env_size + 1)))
		return (0);
	i = 0;
	while (i < env_size)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}
