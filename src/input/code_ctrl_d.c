/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_ctrl_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:17:58 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:27:55 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	code_ctrl_d(void)
{
	if (!(*command() && (*command())[0]))
	{
		ft_default_mode();
		ft_putchar('\n');
	}
}