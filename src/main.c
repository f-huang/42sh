#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"
#include "substitution.h"
#include <signal.h>
#include <stdio.h>//

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
	t_list		*lst;
	t_list		*ptr;

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
			ptr = lst;
			get_heredocs(&ptr);
			while (ptr)
			{
				exec_ast(&sh, ptr->content);
				ptr = ptr->next;
			}
			clear_main(&line, &lst);
		}
		else //CTRL D
		{
			clear_main(&line, &lst);
			ft_putendl("exit");
			clear_shell(&sh);
			exit(0);
		}
	}
	(void)ac;
	return (GOOD);
}
