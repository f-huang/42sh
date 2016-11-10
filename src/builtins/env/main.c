/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:44:26 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/10 15:39:09 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin_env.h"
#include "libft.h"

int			main(int ac, char **av, char **env)
{
	char	**internal_env;
	int		i;
	int		status;

	if (ac < 2)
		return (env_print_env(env));
	internal_env = env_copy_env(env);
	status = env_parse_argv(i, ac, av, &internal_env);
	env_free_env(&internal_env);
	return (status);
}
