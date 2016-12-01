#include <signal.h>
#include "ft_42sh.h"
#include "libft.h"
#include "tools.h"
#include <unistd.h>

/*
**			This function receive the data wrote in the prompt (line).
*/

static int	save_line(char **line, char **buf, size_t size)
{
	if (*line)
	{
		if (!(*line = tl_strrealloc(*line, size)))
			return (ERROR);
		ft_strncat(*line, *buf, size);
	}
	else if (!(*line = tl_strndup(*buf, size)))
		return (ERROR);
	ft_strclr(*buf);
	ft_strdel(buf);
	return (GOOD);
}

static int	push_line(char **tmp, char **line, char **buf, size_t size)
{
	if (!(*tmp = ft_strchr(*buf, '\n')))
		return (save_line(line, buf, size) - 1);
	else
	{
		size = (size_t)(*tmp - *buf);
		return (save_line(line, buf, size));
	}
	return (GOOD);
}

int			get_line(int fd, char **line)
{
	int			ret;
	static char	*tmp;
	char		*buf;

	if ((fd < 0 && 255 < fd) || BUFF_SIZE <= 0 || !line)
		return (ERROR);
	while (tmp)
	{
		if (!(buf = ft_strdup(tmp + 1)))
			return (ERROR);
		if (push_line(&tmp, line, &buf, ft_strlen(buf)))
			return (GOOD);
	}
	if (!(buf = ft_strnew(BUFF_SIZE + 1)))
		return (ERROR);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (ERROR);
		buf[ret] = '\0';
		if (push_line(&tmp, line, &buf, ret))
			return (GOOD);
	}
	return (*line && ft_strlen(*line) > 0 ? GOOD : 0);
}
