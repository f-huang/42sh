/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 03:33:41 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/16 13:28:34 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "execution.h"

/*
**	TEST PURPOSE !
*/

t_redirection		*get_redirection(char **command)
{
	t_redirection	*r;

	if (!(r = (t_redirection*)malloc(sizeof(t_redirection))))
		return (0);
	r->command = (char **)malloc(sizeof(char *) * 3);
	r->command[0] = command[0];
	r->command[1] = 0;//ft_strdup("coucou123");
	r->command[2] = 0;
	r->from_fd = -1;
	r->to_fd = -1;
	r->dest = command[2];
//	r->dest = 0;
	r->type = SIMPLE_REDIRECT | SIMPLE_RIGHT_REDIRECT;
	return (r);
}