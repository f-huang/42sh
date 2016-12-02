/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:34:49 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/02 13:22:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "tools.h"

static char	*build_key(char *p)
{
	char	*key;
	int		i;
	size_t	len;

	i = 1;
	len = 0;
	while (p[i] && (ft_isalnum(p[i]) || p[i] == '_'))
	{
		++len;
		++i;
	}
	if (!(key = tl_strndup(p + 1, len)))
		return (NULL);
	return (key);
}

char		*dollar(t_shell *sh, char *acmd, char *ptr)
{
	char	*p;
	char	*key;
	char	*value;
	char	*save;

	save = NULL;
	if ((p = ft_strchr(ptr, '$')))
	{
		if (!(key = build_key(p)))
			return (NULL);
		value = sh_getenv(sh->lst_env, key);
		if (!(save = ft_memalloc(ft_strlen(acmd) - ft_strlen(key) +\
			(value ? ft_strlen(value) : 0) + 1)))
			return (NULL);
		save = ft_strncat(save, acmd, (size_t)(p - acmd));
		if (value)
			save = ft_strcat(save, value);
		p += ft_strlen(key) + 1;
		save = ft_strcat(save, p);
		ft_strdel(&key);
	}
	ft_strdel(&acmd);
	return (save);
}
