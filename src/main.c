#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"
#include "expansion.h"
#include <signal.h>
#include <stdio.h>//
#include "history.h"

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
		if (get_line(0, &line) == 1)
		{
			save_command_line(&sh.lst_history, line);
			lexer_parser(line, &lst_commands);
			loop_through_commands(&sh, lst_commands);
			clear_main(&line, &lst_commands);
		}
		else //CTRL D
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
