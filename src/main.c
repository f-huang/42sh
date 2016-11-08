#include "ft_42sh.h"

int			main(void)
{
	t_shell	sh;
	if (init_shell(&sh))
		while (prompt(&sh))
			;
	else
		return (ERROR);
	return (GOOD);
}
