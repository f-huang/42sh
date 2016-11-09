/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:44:26 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/09 16:59:15 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env.h"
#include "libft.h"

int			main(int ac, char **av, char **env)
{
	char	**internal_env;
	int		i;

	if (ac < 2)
		return (env_print_env(env));
	internal_env = env_copy_env(env);
	return (env_parse_argv(i, ac, av, &internal_env));
}
