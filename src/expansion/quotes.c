/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:27:22 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/08 14:29:47 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*shift_quotes(char *cmd, int *i)
{
	int		save;
	char	c;

	c = cmd[*i];
	save = cmd[*i + 1] ? 0 : *i;
	while (cmd[++(*i)])
	{
		if (save == 0 && cmd[*i] == c)
			save = *i -1;
		cmd[*i - 1] = cmd[*i];
	}
	ft_strclr(cmd + *i - 1);
	*i = save;
	return (cmd);
}

static char		*shift_backslash(char *cmd, int i)
{
	while (cmd[++i])
	{
		cmd[i - 1] = cmd[i];
	}
	ft_strclr(cmd + i - 1);
	return (cmd);
}

char			*remove_quotes_and_backslash(char *cmd)
{
	int			i;
	_Bool		backslash;

	i = 0;
	while (cmd[i])
	{
		backslash = (i > 0 && cmd[i - 1] == '\\') ? 1 : 0;
		if ((cmd[i] == '\"' || cmd[i] == '\'') && backslash == 0)
			cmd = shift_quotes(cmd, &i);
		else if (cmd[i] == '\\' && backslash == 0)// && !is_escaped_char(cmd[i + 1]))
			cmd = shift_backslash(cmd, i);
		else
			i++;
	}
	return (cmd);
}
