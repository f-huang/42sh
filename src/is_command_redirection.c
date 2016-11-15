/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:35:15 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/15 03:13:54 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		is_command_redirection(char **command)
{
	int		i;

	i = 1;
	while (command[i])
	{
		if (ft_strchr(command[i], '>') || ft_strchr(command[i], '<')
			|| ft_strstr(command[i], ">>") || ft_strstr(command[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}
