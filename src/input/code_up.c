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

#include "ft_42sh.h"

void	code_up(int key)
{
	char	*str;

	str = ft_get_elem(key);
	if ((*dquote() % 2) || (*quote() % 2))
		return ;
	if (*ft_pos() == 1)
		ft_putchar('\a');
	if (!str)
		return ;
	ft_move_left(cor()->x);
	ft_fill_space(cor()->len);
	cor()->x = 0;
	ft_default_mode();
	ft_putstr(str);
	ft_raw_mode();
	cor()->len = ft_strlen(str);
	cor()->x = cor()->len;
	ft_strdel(command());
	*command() = ft_strdup_input(str);
	ft_strdel(&str);
}
