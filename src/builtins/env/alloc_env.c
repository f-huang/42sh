#include "ft_42sh.h"

char	**env_alloc_env(size_t len)
{
	return ((char **)malloc(sizeof(char *) * len + 1));
}
