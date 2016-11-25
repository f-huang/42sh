/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:54 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/25 21:05:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"
#include "ast.h"

static void	debug_print_tree(t_ast *root, int color)
{
	t_ast	*ptr = root;
	if (!ptr)
		return ;
	ft_putendlcol(ptr->str, color == 1 ? YELLOW: CYAN);
	debug_print_tree(ptr->left, 1);
	debug_print_tree(ptr->right, 0);
}

static void		debug_print_tab(char **tab)
{
	if (!tab)
	{
		ft_putendlcol("NULL", RED);
		return;
	}
	int	j = 0;
	while (tab[j])
	{
		ft_putendl(tab[j]);
		j++;
	}
}

static void	debug_print_cmd(t_cmdwr *cmd)
{
	if (!cmd)
		return ;
	debug_print_tab(cmd->command);
	t_redirections	*ptr;
	ptr = cmd->redirs;
	while (ptr)
	{
		ft_putendl("~~~~~~~~~~~~~~~~~~~~~~");
		if (ptr->type & SIMPLE_LEFT_REDIRECT)
			ft_putendlcol("<", MAGENTA);
		else if (ptr->type & SIMPLE_RIGHT_REDIRECT)
			ft_putendlcol(">", MAGENTA);
		else if (ptr->type & DOUBLE_RIGHT_REDIRECT)
			ft_putendlcol(">>", MAGENTA);
		ft_putstr("From fd : ");
		ft_putnbrendl(ptr->from_fd);
		ft_putstr("To fd : ");
		ft_putnbrendl(ptr->to_fd);
		if (ptr->type & CLOSE_REDIRECT)
			ft_putendlcol("Close -", YELLOW);
		else if (ptr->type & FILE_REDIRECT)
			ft_putstr("Dest File : ");
		if (ptr->dest)
			ft_putendlcol(ptr->dest, YELLOW);
		ft_putendl("~~~~~~~~~~~~~~~~~~~~~~");
		ptr = ptr->next;
	}
}

static void	debug_print_cmdwr(t_ast *root)
{
	if (root == NULL)
		return ;
	if (root->operator != COMMAND && root->operator != REDIRECTION)
		ft_putendlcol(root->str, GREEN);
	if (root->cmd1)
	ft_putendl("_____CMD1_____");
	debug_print_cmd(root->cmd1);
	if (root->cmd2)
	ft_putendl("_____CMD2_____");
	debug_print_cmd(root->cmd2);
	debug_print_cmdwr(root->left);
	debug_print_cmdwr(root->right);
}

int			line_to_ast(t_shell *sh, char *line)
{
	t_ast	*tree;

	tree = NULL;
	if (!(tree = ast_create_tree(line)))
		return (ERROR);
	debug_print_tree(tree, 1);
	if (!ast_parse_tree(tree))
	{
		ast_destroy_tree(tree);
		return (ERROR);
	}
	if (!ast_to_cmdwr(&tree))
		return (ERROR);
	debug_print_cmdwr(tree);
	(void)sh;
	return (GOOD);
}
