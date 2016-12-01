/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:39:33 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/01 21:48:55 by fhuang           ###   ########.fr       */
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

static char		*core(t_shell *sh, char *cmd)
{
	char		*ret = NULL;
	size_t		i;
	size_t		len;
	_Bool		single_quote;
	_Bool		backslash;

	i = 0;
	len = ft_strlen(cmd);
	ret = cmd;
	while (i < len)
	{
		backslash = (i > 0 && cmd[i - 1] == '\\') ? 1 : 0;
		single_quote = cmd[i] == '\'' && backslash == 0 ? 1 : 0;
		if (cmd[i] == '$' && backslash == 0 && single_quote == 0)
			cmd = dollar(sh, cmd, cmd + i);
		else if (cmd[i] == '~' && backslash == 0 && single_quote == 0)
			tilde(sh, &cmd);
		else if (cmd[i] == '\'')
			i += jump_to_end_of_quote(cmd + i, cmd[i]);
		i++;
	}
	return (cmd);
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
			cmd->command[i] = core(sh, cmd->command[i]);
			++i;
		}
	}
	return (GOOD);
}
