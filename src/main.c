/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:19:48 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/21 16:22:14 by fhuang           ###   ########.fr       */
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
	while (prompt(&sh))
	{
		g_sh = sh;
		if (get_line(0, &line) == 1)
		{
			save_command_line(&sh.lst_history, line);
			alias_substitution(sh.lst_alias, &line);
			lexer_parser(line, &lst_commands);
			loop_through_commands(&sh, lst_commands);
			clear_main(&line, &lst_commands);
		}
		else
		{
			clear_main(&line, &lst_commands);
			ft_putendl("exit");
			clear_shell(&sh);
			exit(0);
		}
	}
	(void)ac;
	return (GOOD);
}
