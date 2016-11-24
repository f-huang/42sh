/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_with_cmdwr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:32:18 by fhuang            #+#    #+#             */
/*   Updated: 2016/11/24 13:25:09 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "ft_42sh.h"


static void		debug_tabprint(char **tab, char *color)
{
	int		i;
	i = 0;
	while (tab[i])
	{
		ft_putstrcol(tab[i++], color);
		if (tab[i])
			ft_putstr(" - ");
		else
			ft_putchar('\n');
	}
}

static void		debug_print_list(t_ast *list)
{
	while (list)
	{
		if (list->operator == PIPE)
			ft_putstrcol("|    : ", GREEN);
		else if (list->operator == OR)
			ft_putstrcol("||   : ", GREEN);
		else if (list->operator == AND)
			ft_putstrcol("&&   : ", GREEN);
		else if (list->operator == COMMAND)
			ft_putstrcol("cmd  : ", GREEN);
		if (list->cmd1)
			debug_tabprint(list->cmd1->command, CYAN);
		if (list->cmd2)
		{
			if (list->operator == PIPE)
				ft_putstrcol("|    : ", GREEN);
			else if (list->operator == OR)
				ft_putstrcol("||   : ", GREEN);
			else if (list->operator == AND)
				ft_putstrcol("&&   : ", GREEN);
			else if (list->operator == COMMAND)
				ft_putstrcol("cmd  : ", GREEN);
			debug_tabprint(list->cmd2->command, CYAN);
		}
		if (!list->cmd1 && !list->cmd2)
			ft_putendlcol(list->str, MAGENTA);
		list= list->right;
	}
}

/*********************TABSPLIT -> HAS TO BE ANOTHER FUNCTION ---- TEST /!\*******************************/

static int		tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
	{
		i++;
	}
	return (i);
}

static char		**concat_tab(char **tab1, char **tab2)
{
	char	**tab;
	int		len;
	int		i;
	int		j;

	len = tablen(tab1) + tablen(tab2);
	tab = (char**)ft_memalloc(sizeof(char*) * (len+1));
	j = 0;
	i = 0;
	while (tab1[i])
		tab[j++] = tab1[i++];
	if (tab2)
	{
		i = 0;
		while (tab2 && tab2[i])
			tab[j++] = tab2[i++];
		free(tab2);
	}
	free(tab1);
	return (tab);
}
/*********************TABSPLIT -> HAS TO BE ANOTHER FUNCTION ---- TEST /!\*******************************/

static char		**fill_command_tab(t_ast **list, t_ast *ptr)
{
	char	**tab1;
	char	**tab2;

	tab2 = NULL;
	tab1 = ft_strsplit(ptr->str, ' ');
	if (ptr->right && ptr->right->operator == COMMAND)
	{
		tab2 = ft_strsplit(ptr->right->str, ' ');
		tab1 = concat_tab(tab1, tab2);
		ast_remove_link(list, ptr->right);
	}
	return (tab1);
}

static int		set_cmd_pointers(t_ast *ptr, t_cmdwr *cmd, int ret)
{
	if (!ptr->cmd1)
		ptr->cmd1 = cmd;
	else
		ptr->cmd2 = cmd;
	return (ret);
}

static int		link_cmdwr(t_ast **list, t_ast *ptr, t_cmdwr *cmd)
{
	const int	operator[] = {PIPE, OR, AND};
	int			i;

	i = -1;
	while (++i < 3)
	{
		if (ptr->left && ptr->left->operator == operator[i])
			return (set_cmd_pointers(ptr->left, cmd, GOOD));
		else if (ptr->right && ptr->right->operator == operator[i])
			return (set_cmd_pointers(ptr->right, cmd, GOOD));
	}
	(void)list;
	return (set_cmd_pointers(ptr, cmd, ERROR));
}

static t_cmdwr	*create_cmdwr(t_ast **list, t_ast *ptr)
{
	t_cmdwr			*cmd;
	_Bool			file_redirect;

	cmd = NULL;
	file_redirect = false;
	if (!(cmd = (t_cmdwr*)ft_memalloc(sizeof(t_cmdwr))))
		return (NULL);
	if (ptr->right && IS_REDIRECTION(ptr->right->operator))
	{
		if (!(cmd->redir = fill_redirection_struct(list, ptr->right, &file_redirect)))
			return (NULL);
	}
	if (!(cmd->command = fill_command_tab(list, ptr)))
		return (NULL);
	return (cmd);
}

int		ast_create_tree_with_cmdwr(t_ast **list)
{
	t_ast	*ptr;
	t_cmdwr	*cmd;

	ptr = *list;
	while (ptr)
	{
		if (ptr->operator == COMMAND)
		{
			if (!(cmd = create_cmdwr(list, ptr)))
				return (ERROR);
			if (link_cmdwr(list, ptr, cmd))
				ast_remove_link(list, ptr);
		}
		ptr = ptr->right;
	}
	debug_print_list(*list);
	return (GOOD);
}
