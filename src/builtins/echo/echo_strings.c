#include <stdbool.h>
#include "builtin_echo.h"
#include "ft_42sh.h"
#include "libft.h"

static const t_escaped_char		escaped_char[NB_ESC_CHAR] = {
	{'a', "\a"},
	{'b', "\b"},
	{'e', "\e"},
	{'f', "\f"},
	{'n', "\n"},
	{'r', "\r"},
	{'t', "\t"},
	{'v', "\v"},
	{'\\', "\\"}
};

int		echo_escaped_char(char c)
{
	int		i;

	i = 0;
	while (i < NB_ESC_CHAR)
	{
		if (c == escaped_char[i].c)
		{
			if (write(1, escaped_char[i].escaped_char, 1) == -1)
				return (ERROR);
			return (GOOD);
		}
		i++;
	}
	return (ERROR);
}

int		echo_strings(bool option[2], char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (option[1] && str[i] == '\\')
		{
			if (echo_escaped_char(str[++i]))
				i++;
			else
				i--;
		}
		if (write(1, str + i, 1) == -1)
			return (ERROR);
		i++;
	}
	return (GOOD);
}
