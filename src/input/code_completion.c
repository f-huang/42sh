/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:14:56 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/23 19:00:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tools.h"
#include "expansion.h"
#include "input.h"

extern t_shell	g_sh;

#define ALL_BUILTINS "alias cd echo env exit export history read setenv\
unalias unset unsetenv"

static int	search_through_tab(char **tab, char *command)
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
			ft_lstadd(get_list_completion(), ft_lstnew(tab[i], ft_strlen(tab[i]) + 1));
		i++;
	}
	return (found);
}

static int	look_for_a_command(char *command)
{
	char	**tab;
	char	*path;
	int		i;

	tab = ft_strsplit(ALL_BUILTINS, ' ');
	search_through_tab(tab, command);
	tl_freedoubletab(tab);
	tab = NULL;
	if (!(path = sh_getenv(g_sh.lst_env ,"PATH")))
		return (1);
	tab = ft_strsplit(path, ':');
	i = 0;
	while (tab && tab[i])
	{
		search_through_dir(tab[i], command);
		i++;
	}
	tl_freedoubletab(tab);
	return (0);
}

static void	display_command(char *cmd_before, char *to_add, int where)
{
	int		len;

	if (*command() && (*command())[0])
		*command() = tl_switch_string(cmd_before, where, to_add, "");
	else
	{
		ft_strdel(command());
		*command() = ft_strdup(to_add + where);
	}
	default_mode();
	ft_putstr(to_add);
	raw_mode();
	len = ft_strlen(to_add);
	cor()->x += len;
	cor()->len += len;
}

static char	*step_back(char *save, int *i)
{
	int		end;

	end = cor()->x - 1;
	*i = end;
	while (*i >= 0 && !tl_iswhitespace((*command())[*i]) && (*command())[*i] != ';'\
		&& (*command())[*i] != '&' && (*command())[*i] != '|')
	{
		stremove();
		--(*i);
	}
	cor()->len = ft_strlen(*command());
	*i = *i < 0 ? 0 : *i;
	return (tl_strndup(save, end - *i + 1));
}

static void	command_back_to_what_it_was(char *save, int pos)
{
	if (!save)
		return ;
	code_end();
	while (cor()->x)
		stremove();
	cor()->len = 0;
	ft_strdel(command());
	*command() = save;
	default_mode();
	ft_putstr(save);
	raw_mode();
	cor()->x = ft_strlen(save);
	cor()->len = cor()->x;
	move_left(cor()->x - pos);
	cor()->x = pos;
}

void	code_completion(void)
{
	t_list		*cursor = NULL;
	char		*save;
	char		*word;
	int			pos;
	int			i;

	if (!(save = strdup_input(*command())) && !(i = 0))
		return ;
	pos = cor()->x;
	word = step_back(save, &i);
	ft_putendlcol(word, RED);
	if ((cursor = *get_cursor_completion()))
	{
		if (!(*get_cursor_completion() = cursor->next))
			*get_cursor_completion() = *get_list_completion();
	}
	else
	{
		if (i == 0 || is_a_command(save))
			look_for_a_command(tl_isstrempty(save) ? "" : word);
		else
			search_through_dir("./", save + i);
		*get_cursor_completion() = *get_list_completion();
	}
	if ((cursor = *get_cursor_completion()) && cursor->content)
	{
		display_command(*command(), cursor->content, cor()->x);
		ft_strdel(&save);
	}
	else
		command_back_to_what_it_was(save, pos);
	ft_strdel(&word);
// 	else if (str[i - 1] == '$')
// 		look_for_a_variable(str + i);
}
