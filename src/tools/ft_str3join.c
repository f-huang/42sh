#include "libft.h"

/*
**		This function is joining three strings. None of them must be allocated.
**		The returned string should be freed at the end of its use.
*/

char		*ft_str3join(char *s1, char *s2, char *s3)
{
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	ret = ft_strndup(s1, ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	if (ret == NULL)
		return (NULL);
	ret = ft_strcat(ret, s2);
	ret = ft_strcat(ret, s3);
	return (ret);
}
