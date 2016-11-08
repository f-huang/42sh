#include "environment.h"
#include "libft.h"

/*
**		This function searches the environment list to find the
**		environment variable key, and returns a pointer to the corresponding
**		value string.
**
**		You shall not free the returned string.
*/

char		*sh_getenv(t_environment *lst_env, char *key)
{
	t_environment	*link;
	size_t			index;
	char			*tmp;

	link = lst_env;
	while (link && key)
	{
		if ((tmp = ft_strndup(link->variable,\
			(size_t)(ft_strchr(link->variable, '=') - link->variable))))
		{
			if (ft_strequ(key, tmp))
			{
				ft_strdel(&tmp);
				index = 1 + (size_t)(ft_strchr(link->variable, '=') - link->variable);
				return (link->variable + index);
			}
			ft_strdel(&tmp);
		}
		link = link->next;
	}
	return (NULL);
}
