#include "ft_42sh.h"
#include "tools.h"
#include "libft.h"
#include "ast.h"
#include "substitution.h"

#include <stdio.h>//

int				main(int ac, char **av)
{
	t_shell		sh;
	char		*line;
	char		**commands;
	t_list		*lst;
	t_list		*p;
	t_cmdwr		*cmd = (t_cmdwr*)ft_memalloc(sizeof(t_cmdwr));

	line = NULL;
	lst = NULL;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh, av[0]))
		return (ERROR);
	while (prompt(&sh))
	{
		if (get_line(&line) == 1)
		{
			if (first_lexer(line, &lst))
			{
				p = lst;
				while (p)
				{
					cmd->command = ft_strsplit(p->content, ' ');//
					substitute(&sh, cmd);
					p = p->next;
				}
				while (lst)
				{
					if ((commands = ft_strsplit(lst->content, ' ')))
					{
						exec_command(&sh, commands);
						tl_freedoubletab(commands);
						exec_command(&sh, cmd->command);
						tl_freedoubletab(cmd->command);
					}
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
			/* clear all*/
			exit(0);
		}
	}
	(void)ac;
	return (GOOD);
}
