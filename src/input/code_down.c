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

#include "input.h"

void	code_down(int key)
{
	char	*str;

	str = get_elem(key);
	if ((*dquote() % 2) || (*quote() % 2))
		return ;
	if (*pos() == *get_size())
	{
		move_left(cor()->x);
		fill_space(cor()->len);
		cor()->x = 0;
		ft_strdel(command());
		*command() = strdup_input("");
		return ;
	}
	if (!str)
		return ;
	move_left(cor()->x);
	fill_space(cor()->len);
	cor()->x = 0;
	ft_putstr(str);
	cor()->len = ft_strlen(str);
	cor()->x = cor()->len;
	ft_strdel(command());
	*command() = strdup_input(str);
	ft_strdel(&str);
}
