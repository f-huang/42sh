/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:39:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/18 14:39:24 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
/*
static int		tilde(t_shell *sh, char *command)
{
	return (GOOD);
}
*/
static int		dollar(t_shell *sh, char *command)
{
	int		i;
	char	**split_command;
	char	*tmp;
	int		modif;

	i = 0;
	modif = 0;
	if (!(split_command = ft_strsplit(command, ' ')))
		return (ERROR);
	while (split_command[i])
	{
		if (split_command[i][0] == '$')
		{
			if ((tmp = sh_getenv(sh->lst_env, &split_command[i][1])))
			{
				ft_strdel(&split_command[i]);
				if (!(split_command[i] = ft_strdup(tmp)))
					return (ERROR);
				++modif;
			}
		}
		++i;
	}
	if (modif)
	{
		ft_strdel(&command);
		if (!(command = ft_arrtostr(split_command, " ")))
			return (ERROR);
	}
	tl_freedoubletab(split_command);
	return (GOOD);
}

int				substitute(t_shell *sh, t_list **commands)
{
	while (*commands)
	{
		dollar(sh, *commands);
//		tilde(sh, commands->content);
		*commands = *(commands->next);
	}
	return (GOOD);
}
