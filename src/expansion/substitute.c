/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:39:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/11/30 14:20:36 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 **			The substitute function change $key by the value in environment and\
 **			the tilde ~ by the path of home.
 **			Be careful with the simple quotes.
 */

#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "execution.h"
#include "expansion.h"

static size_t		jump_to_end_of_quote(char *cmd, char c)
{
	size_t	i;

	i = 1;
	while (cmd[i] && cmd[i] != c && cmd[i - 1] != '\\')
		++i;
	return (i);
}

static int		core(t_shell *sh, char **acmd)
{
	size_t		i;
	char		*p;
	size_t		len;

	i = 0;
	p = *acmd;
	len = ft_strlen(*acmd);
	while (i < len)
	{
		if (p[i] == '\"')
		{
			dollar(sh, acmd);
			i += jump_to_end_of_quote(&p[i], '\"');
		}
		else if (p[i] == '\'')
			i += jump_to_end_of_quote(&p[i], '\'');
		else
		{
			tilde(sh, acmd);
			dollar(sh, acmd);
		}
		++i;
	}
	return (GOOD);
}

int				substitute(t_shell *sh, t_cmdwr *cmd)
{
	size_t		i;
	size_t		ac;

	ac = tl_arrlen(cmd->command);
	if (ac >= 2)
	{
		i = 1;
		while (i < ac)
		{
			core(sh, &cmd->command[i]);
			++i;
		}
	}
	return (GOOD);
}
