#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"

int				main(int ac, char **av)
{
	t_shell		sh;
	char		*line;
	char		**commands;
//	char		*trim;
	t_list		*lst;

	line = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh, av[0]))
		return (ERROR);
	while (prompt(&sh))
	{
		if (get_line(&line) == 1)
		{
			lst = first_lexer(line);
			while (lst)
			{
				commands = ft_strsplit(lst->content, ' ');
				exec_command(&sh, commands);
//				reset_termios(sh.term);
				tl_freedoubletab(commands);
				lst = lst->next;
			}
			/* lexer */
			ft_strclr(line);
			ft_strdel(&line);
//			ft_strdel(&trim);
		}
		else
		{
			reset_termios(sh.term);
			if (line)
			{
				ft_strclr(line);
				ft_strdel(&line);
			}
			ft_putendl("exit");
			/* clear all*/
			exit(0);
		}
	}
	(void)ac;
	return (GOOD);
}
