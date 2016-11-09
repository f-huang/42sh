#include <stdbool.h>
#include "ft_42sh.h"
#include "libft.h"

static int	is_option(bool option[2], char c)
{
	const char	*letters[] = "Een";
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
	ft_bzero(option, sizeof(int) * 2);
	return (ERROR);
}

int			check_for_options(bool option[2], char *str)
{
	int			i;

	i = 1;
	while (str[i])
	{
		if (!is_option(option, str[i]]))
			return (ERROR);
		i++;
	}
	return (GOOD);
}
