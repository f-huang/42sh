/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:16:31 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/18 20:19:12 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_history.h"
#include "history.h"
#include "tools.h"

int		history_option_p(t_hist_option tools, char **av)
{
	int		i;

	if (!av || !av[0])
		return (0);
	delete_last_entry(tools);
	i = 0;
	while (av[i])
		ft_putendl(av[i++]);
	return (0);
}
