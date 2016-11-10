#include "environment.h"
#include "libft.h"
#include <stdlib.h>

/*
**		This function create a link at the end of the environment list.
**		The variable should already be the correct format ($KEY=$VALUE).
**		The length is then calculated to prevent useless realloc.
*/

static void	push_back(t_environment **lst_env, t_environment *new)
{
	t_environment		*elem;

	if (*lst_env)
	{
		elem = *lst_env;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst_env = new;
}

int			create_elem(t_environment **lst_env, char *variable)
{
	t_environment	*new;

	if (!variable)
		return (ERROR);
	if (!(new = (t_environment*)malloc(sizeof(t_environment))))
		return (ERROR);
	if (!(new->variable = ft_strdup(variable)))
		return (ERROR);
	new->length = ft_strlen(variable);
	push_back(lst_env, new);
	return (GOOD);
}
