/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:34:23 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:34:42 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	code_up(int key)
{
	char	*str;

	str = get_elem(key);
	if ((*dquote() % 2) || (*quote() % 2))
		return ;
	if (*pos() == 1)
		ft_putchar('\a');
	if (!str)
		return ;
	move_left(cor()->x);
	fill_space(cor()->len);
	cor()->x = 0;
	default_mode();
	ft_putstr(str);
	raw_mode();
	cor()->len = ft_strlen(str);
	cor()->x = cor()->len;
	ft_strdel(command());
	*command() = strdup_input(str);
	ft_strdel(&str);
}
