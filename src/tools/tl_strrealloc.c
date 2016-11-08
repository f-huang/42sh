#include "libft.h"

char		*tl_strrealloc(char *s, size_t size)
{
	char	*s2;
	size_t	slen;

	slen = ft_strlen(s);
	if (!(s2 = ft_strnew(slen + size)))
		return (NULL);
	ft_strncpy(s2, s, slen);
	ft_strdel(&s);
	return (s2);
}
