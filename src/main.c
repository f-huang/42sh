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
	// char		**commands;
	t_list		*lst;
	// t_list		*p;
	// t_cmdwr		*cmd = (t_cmdwr*)ft_memalloc(sizeof(t_cmdwr));

	line = NULL;
	lst = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh, av[0]))
		return (ERROR);
	while (prompt(&sh))
	{
		if (get_line(0, &line) == 1)
		{
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
		}
		else
		{
			if (line)
			{
				ft_strclr(line);
				ft_strdel(&line);
				ft_lstdel(&lst, tl_del);
			}
			ft_putendl("exit");
			clear_shell(&sh);
			exit(0);
		}
	}
	(void)ac;
	return (GOOD);
}
