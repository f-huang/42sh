/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_ctrl_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 12:28:51 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/08 12:29:00 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	code_ctrl_w(void)
{
	ft_strdel(copied());
	*copied() = ft_strdup_input(&(*command())[cor()->x]);
}
