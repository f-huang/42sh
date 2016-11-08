#include "libft.h"

char	*tl_strndup(const char *s1, size_t n)
{
	char *s2;

	if (!(s2 = ft_strnew(n)))
		return (NULL);
	return (ft_strncat(s2, s1, n));
}
