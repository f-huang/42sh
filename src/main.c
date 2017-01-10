/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:19:48 by yfuks             #+#    #+#             */
/*   Updated: 2017/01/10 14:58:51 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"
#include "expansion.h"
#include <signal.h>
#include <stdio.h>
#include "history.h"

t_shell		g_sh;

static void		clear_main(char **line, t_list **lst)
{
	if (*line)
	{
		ft_strclr(*line);
		ft_strdel(line);
	}
	if (*lst)
		tl_lstdelast(lst);
}

int				main(int ac, char **av)
{
	t_shell		sh;
	char		*line;
	t_list		*lst_commands;

	lst_commands = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh, av[0]))
		return (ERROR);
	line = NULL;
	*old_command() = ft_strdup("");
	ft_init_list();
	while (prompt(&sh))
	{
		g_sh = sh;
		if (ft_input() == 0)
		{
			ft_strcmp(*command(), *old_command()) ? ft_history(*command()) : 0;
			ft_strdel(old_command());
			*old_command() = *command() ? ft_strdup(*command()) : ft_strdup("");
			save_command_line(&sh.lst_history, *command());
			alias_substitution(sh.lst_alias, command());
			lexer_parser(command(), &lst_commands);
			loop_through_commands(&sh, lst_commands);
			clear_main(command(), &lst_commands);
		}
		else
		{
			clear_main(command(), &lst_commands);
			ft_putendl("exit");
			clear_shell(&sh);
			exit(0);
		}
	}
	(void)ac;
	return (GOOD);
}
