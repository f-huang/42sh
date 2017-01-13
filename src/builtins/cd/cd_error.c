/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:11:49 by cjacquem          #+#    #+#             */
/*   Updated: 2017/01/13 12:26:50 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"

int			cd_error(int index, char *path)
{
	const char	*error_msg[] = {
		"Too many arguments.\n",
		"'HOME' variable not set.\n",
		"'OLDPWD' variable not set.\n",
		": No such file or directory.\n",
		": Not a directory.\n",
		": Permission denied.\n",
		NULL
	};

	if (index == -1)
	{
		if (!exec_is_directory(path) && exec_is_file(path))
			index = 4;
		else if (!exec_is_readable(path) && exec_is_file(path))
			index = 5;
		else
			index = 3;
	}
	ft_putstr_fd("42sh: cd: ", 2);
	if (index > 2 && index < 6 && path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(error_msg[index], 2);
	return (1);
}
