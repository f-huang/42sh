/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:21:06 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/05 18:40:24 by cjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "environment.h"
#include "history.h"

/*
**	This function free every variable in the shell structure
**	and set pointers to NULL.
*/

void	clear_shell(t_shell *sh)
{
	sh->last_return = 0;
	clear_history_list(&sh->lst_history, sh->lst_env);
	clear_env_list(&sh->lst_env);
	clear_env_list(&sh->lst_localvar);
	ft_strdel(&sh->bin_path);
}
