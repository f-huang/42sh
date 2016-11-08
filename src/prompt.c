#include "ft_42sh.h"
#include <signal.h>

int			prompt(t_shell *sh)
{
	char	*line;

	line = NULL;
	ft_putstr(PROMPT);
	if (get_line(&line) == 1)
	{
		/* lexer */
		ft_strclr(line);
		ft_strdel(&line);
	}
	else
	{
		ft_putendl("exit");
		/* clear all */
		exit(0);
	}
	return (GOOD);
}
