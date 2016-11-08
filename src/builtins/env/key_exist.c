#include "ft_42sh.h"
#include "libft.h"

int		env_key_exist(char *key, char **env)
{
	int		i;

	if (env == 0)
		return (0);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], ft_strlen(key)) == 0)
			return (1);
		i++;
	}
	return (0);
}
