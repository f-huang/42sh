#include <stddbool.h>
include "ft_42sh.h"


int			main(int ac, char **av)
{
	bool	is_option;
	bool	option[2];
	int		i;

	i = 1;
	is_option = 1;
	ft_bzero(option, sizeof(int) * 2);
	while (av[i])
	{
		if (is_option && ((is_option = check_for_options(option, av[i]))))
			i++;
		else
		{
			if (!echo_strings(option, av[i]))
				return (ERROR);
			i++;
		}
	}
	return (GOOD);
}
