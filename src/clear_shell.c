/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:21:06 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/30 14:39:46 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "environment.h"

/*
**	This function free every variable in the shell structure
**	and set pointers to NULL.
*/

void	clear_shell(t_shell *sh)
{
	sh->last_return = 0;
	clear_env_list(&sh->lst_env);
	clear_env_list(&sh->lst_localvar);
	ft_strdel(&sh->bin_path);
}
