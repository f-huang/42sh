#include "builtin_env.h"
#include "libft.h"

char	*env_get_env_key(char *str)
{
	char	*key;
	char	*equalsign;

	key = ft_strdup(str);
	equalsign = ft_strchr(key, '=');
	equalsign[0] = 0;
	return (key);
}
