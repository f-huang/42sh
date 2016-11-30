#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ft_42sh.h"
#include "history.h"

int			save_history(t_list *all_history)
{
	int		fd;

	fd = open(HISTORY, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (ERROR);
	while (all_history)
	{
		write(fd, all_history->content, all_history->content_size);
		write(fd, "\n", 1);
		all_history = all_history->next;
	}
	if (close(fd) == -1)
		return (ERROR);
	return (GOOD);
}
