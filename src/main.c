#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"
#include "substitution.h"
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
<<<<<<< HEAD
			save_command_line(&sh.lst_history, line);
			lexer_parser(line, &lst_commands);
			loop_through_commands(&sh, lst_commands);
			clear_main(&line, &lst_commands);
=======
			if (first_lexer(line, &lst))
			{
				ft_lstadd(&sh.all_history, ft_lstnew(line, ft_strlen(line) + 1));
				while (lst)
				{
					exec_ast(&sh, lst->content);
					lst = lst->next;
				}
			}
			ft_strclr(line);
			ft_strdel(&line);
			ft_lstdel(&lst, tl_del);
>>>>>>> 72c4042b0eecd6045b65c415a4cbc45cafb5c815
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
