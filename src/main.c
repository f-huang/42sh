#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "execution.h"

int			main(int ac, char **av)
{
	t_shell		sh;
	char		*line;
	char		**commands;
	char		*trim;

	line = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh, av[0]))
		return (ERROR);
	while (prompt(&sh))
	{
		if (get_line(&line) == 1)
		{
			trim = ft_strtrim(line);
			commands = ft_strsplit(trim, ' ');
			if (*trim && is_command_redirection(commands))
			{
				exec_redirection(&sh, get_redirection(commands));
				ft_putnbr(sh.last_return);
				ft_putchar('\n');
			}
			else if (*trim)
			{
//				exec_command(&sh, commands);
				exec_pipes(&sh);
				ft_putnbr(sh.last_return);
				ft_putchar('\n');
			}
			tl_freedoubletab(commands);
			/* lexer */
			ft_strclr(line);
			ft_strdel(&line);
			ft_strdel(&trim);
		}
		else
		{
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
