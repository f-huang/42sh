/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:27:22 by fhuang            #+#    #+#             */
/*   Updated: 2017/02/03 17:30:07 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_42sh.h"

#define SQUOTE_OPEN (bf.squote % 2) == 1
#define DQUOTE_OPEN (bf.dquote % 2) == 1

static char		*remove_newlines(char *cmd, int i)
{
	while (cmd[i + 1])
	{
		cmd[i] = cmd[i + 1];
		++i;
	}
	ft_strclr(cmd + i);
	return (cmd);
}

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
	int			i;
	t_bitfield	bf;

	i = -1;
	ft_bzero(&bf, sizeof(t_bitfield));
	while (cmd[++i])
	{
		if (cmd[i] == '\n' && i > 0 && cmd[i - 1] == '\\' && !(SQUOTE_OPEN))
		{
			cmd = remove_newlines(cmd, i);
			--i;
		}
		bf.bslash = (i > 0 && cmd[i - 1] == '\\' && !(SQUOTE_OPEN)) ? 1 : 0;
		if (cmd[i] == '\\' && !(SQUOTE_OPEN) && cmd[i + 1] == '\\' && (i++))
			cmd[i] = 127;
		else if (!(SQUOTE_OPEN) && cmd[i] == '\\' &&\
			cmd[i + 1] != '\'' && cmd[i + 1] != '\"' && cmd[i + 1] != '\n')
			cmd[i] = 127;
		else if (cmd[i] == '\'' && !(DQUOTE_OPEN) && bf.bslash == 0 &&\
			(++bf.squote))
			cmd[i] = 127;
		else if (cmd[i] == '\"' && bf.bslash == 0 && !(SQUOTE_OPEN) &&\
			(++bf.dquote))
			cmd[i] = 127;
		else if (bf.bslash == 1 && ((cmd[i] == '\'' && !(DQUOTE_OPEN)) ||\
			(cmd[i] == '\"' && !(SQUOTE_OPEN))))
			cmd[i - 1] = 127;
	}
	return (strcpy_without_blank(cmd));
}
