#include "ft_42sh.h"
#include "tools.h"

int			main(void)
{
	t_shell		sh;
	char		*line;
	char		**commands;
	int			command_status;
	char		*trim;

	line = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh))
		return (ERROR);
	while (prompt(&sh))
	{
		if (get_line(&line) == 1)
		{
			trim = ft_strtrim(line);
			commands = ft_strsplit(trim, ' ');
			exec_command(&sh, commands);
			tl_freedoubletab(commands);
			/* lexer */
			ft_strclr(line);
			ft_strdel(&line);
			ft_strdel(&trim);
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
