/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_mark.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:22:51 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/19 16:45:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"
#include "ft_42sh.h"
#include "history.h"
/*
**	!
**		Start a history substitution, except when followed by a space,
**		tab, the end of the line, `=' or `('.
**	!n
**		Refer to command line n.
**	!-n
**		Refer to the command n lines back.
**	!!
**		Refer to the previous command. This is a synonym for `!-1'.
**	!string
**		Refer to the most recent command starting with string.
**	!#
**		The entire command line typed so far.
**
*/
static int	is_strdigitneg(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

static int	print_from_offset(char **cmd, int *i)
{
	t_list	*lst;
	char	*tmp;
	int		lst_index;
	int		offset;

	lst = *get_full_list();
	lst_index = 0;
	if ((offset = *cmd[*i + 1] == '!' ? -1 : ft_atoi(*cmd + *i)) < 0)
		offset = ft_lstlen(lst) - offset;
	while (lst && lst_index < offset)
	{
		lst_index++;
		lst = lst->next;
	}
	if (offset == 0 || lst_index != offset || !lst || !lst->content)
	{
		ft_putstr_fd("42sh: !", 2);
		ft_putnbr_fd(offset, 2);
		ft_putstr_fd(": event not found\n", 2);
		return (ERROR);
	}
	tmp = ft_strndup(*cmd + *i, ft_nbrlen(offset));
	*cmd = tl_switch_string(*cmd, *i, lst->content, tmp);
	ft_strdel(&tmp);
	(*i)++;
	return (GOOD);
}

static int	command_typed_so_far(char **cmd, int *i)
{
	char	*tmp;

	if (*i == 0)
	{
		ft_putstr_fd("42sh: No such word in event\n", 2);
		return (ERROR);
	}
	tmp = ft_strndup(*cmd, *i);
	*cmd = tl_switch_string(*cmd, *i, "!#", tmp);
	ft_strdel(&tmp);
	(*i)++;
	return (GOOD);
}

char		*exclamation_mark(char *cmd)
{
	int		i;
	int		backslash;

	i = 0;
	while (cmd[i])
	{
		backslash = (i > 0 && cmd[i - 1] == '\\') ? 1 : 0;
		if (cmd[i] == '!' && backslash == 0 && cmd[i + 1] && cmd[i + 1] != '='\
			&& cmd[i + 1] != '\t' && cmd[i + 1] != ' ' && cmd[i + 1] != '(')
		{
			if (is_strdigitneg(cmd + i + 1) || cmd[i + 1] == '!')
			{
				if (!print_from_offset(&cmd, &i))
					return (NULL);
			}
			else if (cmd[i + 1] == '#')
			{
				if (!command_typed_so_far(&cmd, &i))
					return (NULL);
			}
		}
		i++;
	}
	// if (OK)
	// delete_last_entry
}
