/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_ctrl_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:13:29 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/24 19:22:31 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	display_missing(char *tmp)
{
	default_mode();
	tmp = &tmp[cor()->x];
	ft_putstr(tmp);
	move_left(ft_strlen(tmp));
}

void		code_ctrl_r(void)
{
	static char	*tmp = NULL;
	char		*pattern;
	t_list		*full_list;

	if (!(*search_mode()))
	{
		*search_mode() = 1;
		return ;
	}
	pattern = ft_strjoin(*command(), "*");
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
