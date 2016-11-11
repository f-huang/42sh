#include "ft_42sh.h"
#include <signal.h>

int			prompt(t_shell *sh)
{
	(void)sh;
	ft_putstr(PROMPT);
	return (GOOD);
}
