#include "ft_42sh.h"

void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr(PROMPT);
		// need to kill processus
	}
}
