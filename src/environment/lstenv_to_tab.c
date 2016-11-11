/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:53:59 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/11 17:00:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"

static size_t	lstenv_len(t_environment *lst_env)
{
	size_t	i;

	i = 0;
	while (lst_env)
	{
		i++;
		lst_env = lst_env->next;
	}
	return (i);
}

char			**lstenv_to_tab(t_environment *lst_env)
{
	char	**tab;
	int		i;

	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (lstenv_len(lst_env) + 1))))
		return (NULL);
	i = 0;
	while (lst_env)
	{
		tab[i++] = lst_env->variable;
		lst_env = lst_env->next;
	}
	tab[i] = NULL;
	return (tab);
}
