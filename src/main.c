#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"
#include "substitution.h"
#include <signal.h>
#include <stdio.h>//

int				main(int ac, char **av)
{
	t_shell		sh;
	char		*line;
	t_list		*lst;

	lst = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh, av[0]))
		return (ERROR);
	line = NULL;
	while (prompt(&sh))
	{
		if (get_line(&line) == 1)
		{
			lexer_parser(line, &lst);
			//RECUP `<<`
			//PUIS EXEC:
/*			while (lst)
			{
				exec_ast(&sh, lst->content);
				lst = lst->next;
			}*/
		}
		else //CTRL D
		{
			if (line)
				ft_strdel(&line);
			if (lst)
				ft_lstdel(&lst, tl_del);
			ft_putendl("exit");
			clear_shell(&sh);
			exit(0);
		}
		if (line)
			ft_strdel(&line);
		if (lst)
			ft_lstdel(&lst, tl_del);
	}
	(void)ac;
	return (GOOD);
}
