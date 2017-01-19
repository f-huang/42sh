/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:34:49 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/19 17:44:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "tools.h"

#define SPECIAL_VARIABLE "?$0"

static char	*build_key(char *p, int *variable_number)
{
	const char	special_variable[] = SPECIAL_VARIABLE;
	char		*key;
	int			i;
	size_t		len;

	key = NULL;
	len = 0;
	i = -1;
	while (special_variable[++i])
		if (special_variable[i] == *p)
		{
			*variable_number = i;
			len = 1;
			break ;
		}
	if (!len)
	{
		i = -1;
		while (p[++i] && (ft_isalnum(p[i]) || p[i] == '_'))
			++len;
	}
	if (!(key = tl_strndup(p, len)))
		return (NULL);
	return (key);
}

static char	*get_value(t_shell *sh, char *key, int variable_number)
{
	char		*value;

	value = NULL;
	if (variable_number == -1)
	{
		if (!(value = sh_getenv(sh->lst_localvar, key)))
			value = sh_getenv(sh->lst_env, key);
		value = ft_strdup(value);
	}
	else if (variable_number == 0)
		value = ft_itoa(sh->last_return);
	else if (variable_number == 1)
		value = ft_itoa(getpid());
	else if (variable_number == 2)
		value = ft_strdup("42sh");
	return (value);
}

char		*dollar(t_shell *sh, char *acmd, char *ptr)
{
	char		*key;
	char		*value;
	// char		*save;
	int			variable_number;

	// save = NULL;
	variable_number = -1;
	if (!(key = build_key(++ptr, &variable_number)))
		return (NULL);
	value = get_value(sh, key, variable_number);
	// if (!(save = ft_memalloc(ft_strlen(acmd) - ft_strlen(key) +\
	// 	(value ? ft_strlen(value) : 0) + 1)))
	// 	return (NULL);
	// save = ft_strncat(save, acmd, (size_t)(ptr - acmd - 1));
	// if (value)
	// {
	// 	save = ft_strcat(save, value);
	// 	ft_strdel(&value);
	// }
	// ptr += ft_strlen(key);
	// save = ft_strcat(save, ptr);
	acmd = tl_switch_string(acmd, (size_t)(ptr - acmd - 1), value, key - 1);
	ft_strdel(&key);
	ft_strdel(&value);
	// ft_strdel(&acmd);
	return (acmd);
}
