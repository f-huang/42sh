#include "environment.h"
#include "tools.h"
#include "libft.h"
/*
**		This function adds the variable name to the environment list with the given value.
**		If key does exist in the environment, then its value is changed,
**		if length if big enough, the string is not reallocated;
**		Else key and value are added at the end of the list.
*/

static int	switch_value(t_environment **link, char *key, char *value)
{
	int		len;

	if ((len = ft_strlen(key) + ft_strlen(value) + 1 > (*link)->length))
	{
		ft_strdel(&(*link)->variable);
		if (!((*link)->variable = ft_str3join(key, "=", value))) //
			return (ERROR);
		(*link)->length = len;
	}
	else
	{
		ft_strclr((*link)->variable + ft_strlen(key) + 1);
		(*link)->variable = ft_strcat((*link)->variable, value);
	}
	return (GOOD);
}

static int	add_value(t_environment **lst_env, char *key, char *value)
{
	char	*variable;

	if (!(variable = ft_str3join(key, "=", value)))
		return (ERROR);
	if (!create_link(lst_env, variable))
	{
		ft_strdel(&variable);
		return (ERROR);
	}
	ft_strdel(&variable);
	return (GOOD);
}

int			sh_setenv(t_environment **lst_env, char *key, char *value)
{
	t_environment	*link;
	char			*tmp;
	int				ret;

	link = *lst_env;
	while (link && key)
	{
		if ((tmp = ft_strndup(link->variable,\
			(size_t)(ft_strchr(link->variable, '=') - link->variable))))
		{
			if (ft_strequ(key, tmp))
			{
				ret = switch_value(&link, key, value);
				ft_strdel(&tmp);
				return (ret);
			}
			ft_strdel(&tmp);
		}
		link = link->next;
	}
	return (add_value(lst_env, key, value));
}
