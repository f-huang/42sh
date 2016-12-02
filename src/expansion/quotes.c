/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:27:22 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/02 17:23:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*shift_quotes(char *cmd, int *i)
{
	int		ret;
	char	c;

	ret = 0;
	c = cmd[*i];
	while (cmd[++(*i)])
	{
		if (ret == 0 && cmd[*i] == c)
			ret = *i -1;
		cmd[*i - 1] = cmd[*i];
	}
	ft_strclr(cmd + *i - 2);
	*i = ret;
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

static	int		is_escaped_char(int c)
{
	static const char	escape_char[] = "abefnrtv\\";
	int					i;

	i = 0;
	while (escape_char[i])
	{
		if (escape_char[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char		*remove_backslash(char *cmd)
{
	int			i;
	_Bool		backslash;

	i = 0;
	while (cmd[i])
	{
		backslash = (i > 0 && cmd[i - 1] == '\\') ? 1 : 0;
		if (cmd[i] == '\\' && backslash == 0 && !is_escaped_char(cmd[i + 1]))
			cmd = shift_backslash(cmd, i);
		i++;
	}
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
		else
			i++;
	}
	return (remove_backslash(cmd));
}
