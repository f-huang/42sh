/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:30:16 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:30:41 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	code_down(int key)
{
	char	*str;

	str = ft_get_elem(key);
	if ((*dquote() % 2) || (*quote() % 2))
		return ;
	if (*ft_pos() == *ft_get_size())
	{
		ft_move_left(cor()->x);
		ft_fill_space(cor()->len);
		cor()->x = 0;
		ft_strdel(command());
		*command() = ft_strdup_input("");
		return ;
	}
	if (!str)
		return ;
	ft_move_left(cor()->x);
	ft_fill_space(cor()->len);
	cor()->x = 0;
	ft_putstr(str);
	cor()->len = ft_strlen(str);
	cor()->x = cor()->len;
	ft_strdel(command());
	*command() = ft_strdup_input(str);
	ft_strdel(&str);
}
