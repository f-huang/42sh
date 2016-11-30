#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_42sh.h"
#include "history.h"

int			init_history(t_list **all_history)
{
	int		fd;
	char	*line;

	fd = open(HISTORY, O_RDONLY, S_IRUSR | S_IWUSR);//cf. openat
	ft_putnbr(fd);//
	ft_putchar('\n');//
	if (fd == -1)
		return (ERROR);
	line = NULL;
	while (get_line(fd, &line))
		ft_lstadd(all_history, ft_lstnew(line, ft_strlen(line) + 1));
	if (close(fd) == -1)
		return (ERROR);
	return (GOOD);
}
