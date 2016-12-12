/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_through_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:18:37 by fhuang            #+#    #+#             */
/*   Updated: 2016/12/12 19:07:34 by yfuks            ###   ########.fr       */
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

static void	loop_through_ast(t_shell *sh, t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->cmd1)
		handle_expansion(sh, tree->cmd1);
	if (tree->cmd2)
		handle_expansion(sh, tree->cmd2);
	loop_through_ast(sh, tree->left);
	loop_through_ast(sh, tree->right);
}

void		loop_through_commands(t_shell *sh, t_list *lst_commands)
{
	t_list		*ptr;

	ptr = lst_commands;
	get_heredocs(sh, &ptr);
	while (ptr)
	{
		sh->first_pipe = 1;
		loop_through_ast(sh, ptr->content);
		exec_ast(sh, ptr->content);
		ptr = ptr->next;
	}
}
