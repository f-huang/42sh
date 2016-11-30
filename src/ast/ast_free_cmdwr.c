/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free_cmdwr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:34:49 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/30 16:09:03 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "tools.h"

void	ast_free_cmdwr(t_cmdwr **cmd)
{
	t_redirections	*ptr;
	t_redirections	*tmp;

	if (!*cmd)
		return ;
	if ((*cmd)->command)
	{
		tl_freedoubletab((*cmd)->command);
	}
	if ((*cmd)->redirs)
	{
		ptr = (*cmd)->redirs;
		tmp = NULL;
		while (ptr)
		{
			tmp = ptr;
			ptr = ptr->next;
			if (ptr->dest)
				ft_strdel(&ptr->dest);
			ft_memdel((void*)&ptr);
		}
	}
	free(*cmd);
	*cmd = NULL;
}
