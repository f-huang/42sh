/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:08:58 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/08 14:50:15 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "environment.h"
#include "libft.h"
#include <stdlib.h>

static	char	*get_name(t_shell *sh)
{
	char	*user;

	user = sh_getenv(sh->lst_env, "USER");
	if (user == 0)
		return (0);
	return (ft_strdup(user));
}

static	char	*get_path_from_pwd(t_shell *sh)
{
	char	*pwd;
	char	*home;
	char	*chain;
	char	*tmp;
	int		i;

	pwd = sh_getenv(sh->lst_env, "PWD");
	home = sh_getenv(sh->lst_env, "HOME");
	if (!home || !pwd)
		return (NULL);
	if (!ft_strstr(pwd, home))
		return (ft_strdup(pwd));
	i = 0;
	while (pwd[i] && home[i] && pwd[i] == home[i])
		i++;
	tmp = ft_strdup(&pwd[i]);
	chain = ft_strjoin("~", tmp);
	free(tmp);
	return (chain);
}

int				prompt(t_shell *sh)
{
	char	*pwd;
	char	*user;
	int		length;

	length = 0;
	if ((user = get_name(sh)))
	{
		ft_putstr("\033[1;32m");
		ft_putstr(user);
		ft_putstr("\x1b[0m");
		length += ft_strlen(user);
		free(user);
		ft_putchar(' ');
	}
	else
		ft_putstr("$");
	if ((pwd = get_path_from_pwd(sh)))
	{
		ft_putstr(pwd);
		length += ft_strlen(pwd);
		free(pwd);
	}
	ft_putstr("> ");
	length += ft_strlen("> ");
	return (length);
}
