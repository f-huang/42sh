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
	t_environment	*elem;
	char			*tmp_key;
	size_t			len_key;

	elem = lst_env;
	while (elem && key)
	{
	 	len_key = (size_t)(ft_strchr(elem->variable, '=') - elem->variable);
		if ((tmp_key = ft_strndup(elem->variable, len_key)))
		{
			if (ft_strequ(key, tmp_key))
			{
				ft_strdel(&tmp_key);
				return (elem->variable + ++len_key);
			}
			ft_strdel(&tmp_key);
		}
		elem = elem->next;
	}
	return (NULL);
}
