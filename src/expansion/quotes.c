/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:27:22 by fhuang            #+#    #+#             */
/*   Updated: 2017/02/02 16:38:11 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"

#define SQUOTE_OPEN (squote % 2) == 1
#define DQUOTE_OPEN (dquote % 2) == 1

static char		*strcpy_without_blank(char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != 127)
			src[j++] = src[i];
		i++;
	}
	ft_strclr(src + j);
	return (src);
}

char			*remove_quotes_and_backslash(char *cmd)
{
	int		i;
	int		squote;
	int		dquote;
	_Bool	backslash;

	i = 0;
	squote = 0;
	dquote = 0;
	while (cmd[i])
	{
		backslash = (i > 0 && cmd[i - 1] == '\\' && !(SQUOTE_OPEN)) ? 1 : 0;
		if (cmd[i] == '\n' && backslash == 1 && !(SQUOTE_OPEN) && !(DQUOTE_OPEN))
			cmd[i] = 127;
		else if (cmd[i] == '\'' && !(DQUOTE_OPEN) &&\
			(backslash == 0))
		{
			cmd[i] = 127;
			++squote;
		}
		else if (cmd[i] == '\"' && backslash == 0 && !(SQUOTE_OPEN))
		{
			++dquote;
			cmd[i] = 127;
		}
		else if (cmd[i] == '\\' && !(SQUOTE_OPEN) && cmd[i + 1] == '\\')
		{
			cmd[i + 1] = 127;
			i++;
		}
		else if (cmd[i] == '\\' && !(SQUOTE_OPEN) && cmd[i + 1] != '\'' && cmd[i + 1] != '\"' && cmd[i + 1] != '\n')
			cmd[i] = 127;
		else if (cmd[i] == '\'' && backslash == 1 && !(DQUOTE_OPEN))
			cmd[i - 1] = 127;
		else if (cmd[i] == '\"' && backslash == 1 && !(SQUOTE_OPEN))
			cmd[i - 1] = 127;
		i++;
	}
	return (strcpy_without_blank(cmd));
}
