/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:39:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/23 12:51:43 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 **			The substitute function change $key by the value in environment and\
 **			the tilde ~ by the path of home.
 */

#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"

static int		dollar(t_shell *sh, char **key)
{
	char	*p;
	char	**split_dollar;
	int		i;

	i = 0;
	if (!(split_dollar = ft_strsplit(*key, '$')))
		return (ERROR);
	while (split_dollar[i])
	{
		if ((p = sh_getenv(sh->lst_env, split_dollar[i])))
		{
			ft_strdel(split_dollar[i]);
			if (!(split_dollar[i] = ft_strdup(p)))
				return (ERROR);
		}
		++i;
	}
	return (GOOD);
}

static int		tilde(t_shell *sh, char **key)
{
	char	*p;

	if ((p = sh_getenv(sh->lst_env, "HOME")))
	{
		ft_strdel(key);
		if (!(*key = ft_strdup(p)))
			return (ERROR);
	}
	return (GOOD);
}

int				substitute(t_shell *sh, void **command)
{
	int		i;
	int		modif;
	char	**split_command;

	i = 0;
	modif = 0;
	if (!(split_command = ft_strsplit(*command, ' ')))
		return (ERROR);
	while (split_command[i])
	{
		if (split_command[i][0] == '$' && ++modif)
			dollar(sh, &split_command[i]);
		else if (split_command[i][0] == '~' && ++modif)
			tilde(sh, &split_command[i]);
		++i;
	}
	//	i = 0;//
	//	while (split_command[i])//
	//	{//
	//		ft_putendl(split_command[i]);//
	//		++i;//
	//	}//
	//	ft_putendl_color(*command, RED);//
	if (modif)
	{
		ft_memdel(command);
		if (!(*command = ft_arrtostr(split_command, " ")))
			return (ERROR);
	}
	tl_freedoubletab(split_command);
	return (GOOD);
}
