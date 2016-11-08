#include "ft_42sh.h"

int			main(void)
{
	t_shell		sh;

	if (!init_shell(&sh))
		return (ERROR);
	while (prompt(&sh))
			;
	return (GOOD);
}
