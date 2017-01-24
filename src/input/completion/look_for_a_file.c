/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_a_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 12:18:44 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/24 14:45:37 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"
#include "input.h"

int		look_for_a_file(char *command)
{
	int		len;
	char	*dir_name;

	len = ft_strlen(command) - 1;
	while (len >= 0 && command[len] != '/')
		--len;
	if (len == -1)
	{
		dir_name = ft_strdup(".");
		++len;
	}
	else
	{
		dir_name = tl_strndup(command, len);
		command[len] == '/' ? len++ : 0;
	}
	return (search_through_dir(dir_name, command + len));
}
