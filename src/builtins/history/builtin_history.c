/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 13:28:18 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/17 17:55:41 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"
#include "input.h"

int				builtin_history(t_shell *sh, int ac, char **av)
{
	t_list		*lst;
//	size_t		i;
	int			option;

	lst = *get_list();
	option = 0;
//	if ((i = get_option(av, &option)))
//		return (-1);
	(void)sh;
	(void)ac;
	(void)av;
	return (0);
}
