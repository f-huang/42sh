/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:34:49 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/30 14:29:04 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "tools.h"

static char	*save_before(char *s, char	*p)
{
	char	*save;
	size_t	len;

	len = p - s;
	if (!(save = len ? tl_strndup(s, len) : ft_memalloc(1)))
		return (NULL);
	return (save);
}

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

static char	*save_remain(char *s, char *rest)
{
	char	*save;

	save = ft_strjoin(s, rest);
	ft_strdel(&s);
	return (save);
}

int			dollar(t_shell *sh, char **acmd)
{
	char	*p;
	char	*key;
	char	*value;
	char	*save;

	if ((p = ft_strchr(*acmd, '$')))
	{
		key = build_key(p);
		value = sh_getenv(sh->lst_env, key);
		save = save_before(*acmd, p);
		save = tl_strmerge(save, value);
		save = save_remain(save, p + (ft_strlen(key) + 1));
		ft_strdel(acmd);
		*acmd = save;
		ft_strdel(&key);
	}
	return (GOOD);
}
