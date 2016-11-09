#include "ft_42sh.h"
#include <signal.h>

int			prompt(t_shell *sh)
{
	ft_putstr(PROMPT);
	return (GOOD);
}
