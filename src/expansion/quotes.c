/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:27:22 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/08 15:26:17 by fhuang           ###   ########.fr       */
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

// static	int		is_escaped_char(int c)
// {
// 	static const char	escape_char[] = "abefnrtv\\";
// 	int					i;
//
// 	i = 0;
// 	while (escape_char[i])
// 	{
// 		if (escape_char[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

static char		*remove_backslash(char *cmd)
{
	int			i;
	_Bool		backslash;

	i = 0;
	while (cmd[i])
	{
		backslash = (i > 0 && cmd[i - 1] == '\\') ? 1 : 0;
		if (cmd[i] == '\\' && backslash == 0 &&\
			(cmd[i + 1] == '\'' || cmd[i + 1] == '\"' || cmd[i + 1] != '\\'))
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
		else if (cmd[i] == '\\' && backslash == 0 &&\
			cmd[i + 1] != '\'' && cmd[i + 1] != '\"' && cmd[i + 1] != '\\')
			cmd = shift_backslash(cmd, i);
		else
			i++;
	}
	return (remove_backslash(cmd));
}
