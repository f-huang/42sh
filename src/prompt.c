/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:08:58 by yfuks             #+#    #+#             */
/*   Updated: 2017/01/13 16:24:59 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <limits.h>
#include "ft_42sh.h"
#include "environment.h"
#include "libft.h"
#include "input.h"

static	char	*get_path_from_pwd(t_shell *sh)
{
	char	*pwd;
	char	*home;
	char	*chain;
	char	*tmp;
	int		i;

	pwd = sh_getenv(sh->lst_env, "PWD");
	home = getpwuid(getuid())->pw_dir;
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

	if ((user = getpwuid(getuid())->pw_name))
	{
		ft_putstr("\033[1;32m");
		ft_putstr(user);
		ft_putstr("\x1b[0m");
		ft_putchar(' ');
	}
	else
		ft_putstr("$");
	length = 2 + (user ? ft_strlen(user) : 1);
	if ((pwd = get_path_from_pwd(sh)))
	{
		ft_putstr(pwd);
		length += ft_strlen(pwd);
		free(pwd);
	}
	ft_putstr("> ");
	*prompt_len() = length;
	return (length);
}
