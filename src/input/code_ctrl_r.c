/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_ctrl_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:13:29 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/24 19:08:04 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	display_missing()
{
	
}

void		code_ctrl_r(void)
{
	static char	*tmp = NULL;
	char		*pattern;
	t_list		*full_list;

	pattern = ft_strjoin(*command(), "*");
	*search_mode() = 1;
	full_list = *get_full_list();
	while (full_list)
	{
		if (match((char *)full_list->content, pattern))
		{
			tmp = ft_strdup((char *)full_list->content);
			break ;
		}
		full_list = full_list->next;
	}
	display_missing(tmp);
}
