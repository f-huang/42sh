/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:52:07 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/18 20:17:02 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_history.h"
#include "history.h"
#include "tools.h"

static char	*tab_to_str(char **tab)
{
	char	*ret;
	int		i;

	if (!tab)
		return (NULL);
	i = 0;
	ret = NULL;
	while (tab[i])
	{
		ret = ret ? tl_str3join(ret, " ", tab[i]) : ft_strdup(tab[i]);
		if (!ret)
			return (NULL);
		i++;
	}
	return (ret);
}

int		history_option_s(t_hist_option tools, char **av)
{
	char	*str;

	if (!av || !av[0])
		return (0);
	delete_last_entry(tools);
	if (!(str = tab_to_str(av)))
		return (1);
	save_command_line(str);
	ft_strdel(&str);
	return (0);
}
