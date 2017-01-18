/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:30:16 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/18 15:54:13 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	code_down(int key)
{
	char	*str;

	if (!(str = get_elem(key)) || (*dquote() % 2) || (*quote() % 2))
	{
		ft_putstr("\a");
		return ;
	}
	move_left(cor()->x);
	fill_space(cor()->len);
	cor()->x = 0;
	if (*pos() == *get_size())
	{
		ft_strdel(command());
		*command() = strdup_input("");
		ft_putstr("\a");
		return ;
	}
	ft_putstr(str);
	cor()->len = ft_strlen(str);
	cor()->x = cor()->len;
	ft_strdel(command());
	*command() = strdup_input(str);
	ft_strdel(&str);
}
