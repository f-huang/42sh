#include "ft_42sh.h"

int			main(void)
{
	t_shell		sh;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		;
	if (!init_shell(&sh))
		return (ERROR);
	while (prompt(&sh))
		;
	return (GOOD);
}
