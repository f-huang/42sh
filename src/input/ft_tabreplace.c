/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:59:40 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 13:05:51 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		ft_tabreplace(char ***tab, char *str, char *by)
{
	size_t	i;
	char	*cleaner_str;
	char	**cleaner;

	i = 0;
	cleaner_str = ft_strjoin(str, "=");
	while ((*tab)[i])
	{
		if (!ft_strncmp((*tab)[i], cleaner_str, ft_strlen(cleaner_str)))
		{
			if (by)
				break ;
			else
				(*tab)[i][0] = 0;
		}
		i++;
	}
	ft_strdel(&cleaner_str);
	if (by)
		(*tab)[i] ? free((*tab)[i]) : 0;
	(by) ? (*tab)[i] = ft_strdup_input(by) : 0;
	cleaner = *tab;
	*tab = ft_tabdup(*tab);
	ft_tabdel(&cleaner);
	return (i);
}

char	*ft_newclean(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (ft_isprint(str[i]))
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}
