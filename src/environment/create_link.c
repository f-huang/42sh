#include "environment.h"
#include "libft.h"

/*
**		This function create a link at the end of the environment list.
**		The variable should already be the correct format ($KEY=$VALUE).
**		The length is then calculated to prevent useless realloc.
*/

static void	push_back(t_environment **lst_env, t_environment *new)
{
	t_environment		*link;

	link = *lst_env;
	while (link->next)
		link = link->next;
	link->next = new;
}

int			create_link(t_environment **lst_env, char *variable)
{
	t_environment	*new;

	if (!variable)
		return (ERROR);
	if (!(new = (t_environment*)ft_memalloc(sizeof(t_environment))))
		return (ERROR);
	if (!(new->variable = ft_strdup(variable)))
		return (ERROR);
	new->length = ft_strlen(variable);
	if (*lst_env)
		push_back(lst_env, new);
	else
		*lst_env = new;
	return (GOOD);
}
