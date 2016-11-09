#include "ft_42sh.h"

int			main(void)
{
	t_shell		sh;
	char		*line;

	line = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh))
		return (ERROR);
	while (prompt(&sh))
	{
		if (get_line(&line) == 1)
		{
			/* lexer */
			ft_strclr(line);
			ft_strdel(&line);
		}
		else
		{
			ft_strclr(line);
			ft_strdel(&line);
			ft_putendl("exit");
			/* clear all */
			exit(0);
		}
	}
	return (GOOD);
}
