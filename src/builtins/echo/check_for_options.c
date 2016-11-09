#include <stdbool.h>
#include "ft_42sh.h"
#include "libft.h"

static int	is_option(bool option[2], char c)
{
	const char	letters[] = "Een";
	int			i;

	i = 0;
	while (letters[i])
	{
		if (c == letters[i])
		{
			if (i == 2)
				option[0] = 1;
			else if (i == 1)
				option[1] = 1;
			else
				option[1] = 0;
			return (GOOD);
		}
		i++;
	}
	return (ERROR);
}

int			check_for_options(bool option[2], char *str)
{
	static int	good = 0;
	int			i;

	i = 1;
	if (str[i] == 0)
		return (ERROR);
	while (str[i])
	{
		if (!is_option(option, str[i]))
		{
			if (!good)
				ft_bzero(option, sizeof(bool) * 2);
			return (ERROR);
		}
		i++;
	}
	good = 1;
	return (GOOD);
}
