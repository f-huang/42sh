/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_completion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <ataguiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 11:37:13 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/25 12:21:17 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "ft_42sh.h"
#include "tools.h"

int		check_builtins(char *pattern)
{
	char	**split;
	int		i;
	int		p;

	i = 0;
	p = 0;
	split = ft_strsplit_whitespace("cd exit read unalias setenv echo unset\
			alias export env unsetenv history");
	while (split[i])
	{
		if (match(split[i], pattern) && (*command())[0])
		{
			while (cor()->x > 0
					&& !ft_isspace(ft_getlast(*command())))
				stremove();
			while (split[i][p])
				manage_command(split[i][p++]);
			tl_freedoubletab(split);
			split = NULL;
			return (1);
		}
		i++;
	}
	tl_freedoubletab(split);
	return (0);
}
