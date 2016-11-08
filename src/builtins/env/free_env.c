#include "builtin_env.h"
#include <stdlib.h>
#include "libft.h"

void	env_free_env(char ***env)
{
	int		i;

	i = 0;
	while (env[0][i])
	{
		free(env[0][i]);
		i++;
	}
	free(*env);
	*env = 0;
}
