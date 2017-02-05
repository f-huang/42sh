/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_substitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoac <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 15:55:25 by tpoac             #+#    #+#             */
/*   Updated: 2017/01/31 13:30:30 by tpoac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_list			*glob_substitution(t_list **lst_tab)
{
	t_list		*tmp;
	t_list		*glob;
	t_list		*result;

	if (!lst_tab || !*lst_tab)
		return (0);
	tmp = *lst_tab;
	glob = NULL;
	result = NULL;
	while (tmp)
	{
		glob = ft_glob(tmp->content);
		if (result)
			tl_lstaddend(&result, glob);
		else
			result = glob;
		free(tmp->content);
		tmp = tmp->next;
	}
	return (result);
}
