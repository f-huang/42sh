/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:14:56 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/21 15:52:00 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"
#include "expansion.h"
#include "input.h"

extern t_shell	g_sh;

#define ALL_BUILTINS "alias cd echo env exit export history read setenv\
						unalias unset unsetenv"

static int	search_through_tab(t_list **lst_completion, char **tab, char *command)
{
	int		i;
	int		len;
	int		found;

	i = 0;
	len = ft_strlen(command);
	found = 0;
	while (tab && tab[i])
	{
		if (ft_strnequ(command, tab[i], len) && (found = 1))
			ft_lstadd(lst_completion, ft_lstnew(tab[i], ft_strlen(tab[i]) + 1));
		i++;
	}
	return (found);
}

static int	search_through_dir(t_list **lst_completion, char *dir_name, char *command)
{
	DIR			*dir;
	t_dirent	*sd;
	int		len;

	if ((dir = opendir(*dir_name == '\0' ? "." : dir_name)) == NULL)
		return (1);
	len = ft_strlen(command);
	while ((sd = readdir(dir)))
	{
		if (ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, ".."))
			continue;
		if (ft_strnequ(sd->d_name, command, len))
			ft_lstadd(lst_completion, ft_lstnew(sd->d_name, ft_strlen(sd->d_name) + 1));
	}
	return (closedir(dir) == -1 ? 1 : 0);
}

static int	look_for_a_command(t_list **lst_completion, char *command, int semi_colon)
{
	char	**tab;
	char	*path;
	int		i;

	tab = ft_strsplit(ALL_BUILTINS, ' ');
	search_through_tab(lst_completion, tab, semi_colon ? "" : command);
	tl_freedoubletab(tab);
	tab = NULL;
	if (!(path = sh_getenv(g_sh.lst_env ,"PATH")))
		return (1);
	tab = ft_strsplit(path, ':');
	i = 0;
	while (tab && tab[i])
	{
		search_through_dir(lst_completion, tab[i], semi_colon ? "" : command);
		i++;
	}

	t_list	*lst;

	lst = *lst_completion;
	while (lst)
	{
		if (lst->content)
			ft_putendlcol(lst->content, RED);
		lst = lst->next;
	}
	return (0);
}

static int	is_first_word(char *command)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (tl_iswhitespace(command[i]))
			return (0);
		i++;
	}
	return (1);
}

void	code_completion(void)
{
	static t_list	*lst_completion = NULL;
	static t_list	*cursor = NULL;
	static char		*str = NULL;
	int				i;
	int				len;

	if (ft_strequ(str, *command()))
	{
		cursor = cursor->next;
		if (!cursor)
			cursor = lst_completion;
	}
	else
	{
		str = substitute(&g_sh, ft_strdup(*command()));
		len = cor()->x - 1;
		i = len;
		while (i > 0 && !tl_iswhitespace(str[i]))
			i--;
		if (i == 0 || is_first_word(str + i) || str[len] == ';')
			look_for_a_command(&lst_completion, str + i, str[len] == ';' ? 1 : 0);
		cursor = lst_completion;
		
	}
// 	else if (str[i - 1] == '$')
// 		look_for_a_variable(str + i);
// 	else
// 		look_for_a_file(str + i);
}
