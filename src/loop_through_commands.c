/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_through_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:18:37 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/02 15:19:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include "expansion.h"
#include "execution.h"
#include "tools.h"
#include "ft_42sh.h"

static void	handle_expansion(t_shell *sh, t_cmdwr *cmd)
{
	size_t		i;

	i = 0;
	while (cmd->command[i])
	{
		cmd->command[i] = substitute(sh, cmd->command[i]);
		++i;
	}
}

void	loop_through_commands(t_shell *sh, t_list *lst_commands)
{
	t_list		*ptr;

	ptr = lst_commands;
	while (ptr)
	{
		if (((t_ast*)ptr->content)->cmd1)
			handle_expansion(sh, ((t_ast*)ptr->content)->cmd1);
		if (((t_ast*)ptr->content)->cmd2)
			handle_expansion(sh, ((t_ast*)ptr->content)->cmd2);
		exec_ast(sh, ptr->content);
		ptr = ptr->next;
	}
}
