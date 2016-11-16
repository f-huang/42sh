#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"

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
			if (*trim)
			{
				line_to_ast(&sh, line);
				exec_command(&sh, commands);
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

// echo -n tata tutu 2>&- "test2" titi &&& cat test2

//1)LINE -> COMMANDS -> ;
	//	/!\  Careful : () {} [] "" '' , etc.

//2)COMMANDS[i] -> LIST TOKENS
	// ex : {echo -n tata tutu} {2>& -} {"test 2" titi} {&&} {&} {cat test 2}

//3)CHECK LIST TOKENS VALID
	//ex: 'parse error near '&&'

//4)LIST TOKENS TO AST
	// ex:
	/*							{&&}
							  /		\
						 {2>&-}		[cat test 2]
						/	  \
	[echo -n tata tutu titi]	"test 2"
	*/
