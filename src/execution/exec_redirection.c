/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:07:16 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/16 13:24:20 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>

int		exec_redirection(t_shell *sh, t_redirection *r)
{
	if (r->type & SIMPLE_RIGHT_REDIRECT)
		return (exec_right_redirect(sh, r));
	free(r->dest);
	free(r);
	return (0);
}
