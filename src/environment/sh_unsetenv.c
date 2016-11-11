#include "environment.h"
#include "libft.h"
#include "tools.h"

/*
**		This function searches the environment list to find the
**		environment variable key, and remove the corresponding
**		environment variable.
**
**		Return GOOD on success, and ERROR if the key was not found.
*/

static int	delete_elem(t_environment **elem, t_environment **prev)
{
	if (*prev)
		(*prev)->next = (*elem)->next;
	ft_strdel(&(*elem)->variable);
	ft_memdel((void*)&(*elem));
	return (GOOD);
}

int			sh_unsetenv(t_environment **lst_env, char *key)
{
	t_environment	*elem;
	t_environment	*prev;
	char			*tmp_key;
	size_t			len_key;

	elem = *lst_env;
	prev = NULL;
	while (elem && key)
	{
	 	len_key = (size_t)(ft_strchr(elem->variable, '=') - elem->variable);
		if ((tmp_key = tl_strndup(elem->variable, len_key)))
		{
			if (ft_strequ(key, tmp_key))
			{
				ft_strdel(&tmp_key);
				return (delete_elem(&elem, &prev));
			}
			ft_strdel(&tmp_key);
		}
		prev = elem;
		elem = elem->next;
	}
	return (ERROR);
}
