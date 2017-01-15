/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_completion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 11:37:13 by ataguiro          #+#    #+#             */
/*   Updated: 2017/01/15 18:07:06 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "ft_42sh.h"

int		check_builtins(char *pattern)
{
	char	**split;
	int		i;
	int		p;

	i = 0;
	p = 0;
	split = ft_strsplit_whitespace("cd exit read unalias setenv echo unset\
			alias export env unsetenv");
	while (split[i])
	{
		if (match(split[i], pattern) && (*command())[0])
		{
			while (cor()->x > 0
					&& !ft_isspace(ft_getlast(*command())))
				stremove();
			while (split[i][p])
				manage_command(split[i][p++]);
			ft_tabdel(&split);
			return (1);
		}
		i++;
	}
	ft_tabdel(&split);
	return (0);
}
