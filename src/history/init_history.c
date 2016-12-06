/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquem <cjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:02:09 by cjacquem          #+#    #+#             */
/*   Updated: 2016/12/06 18:17:22 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include "ft_42sh.h"
#include "history.h"
#include "libft.h"
#include "environment.h"
#include "tools.h"

int				init_history(t_history **lst_history, t_variable *lst_env)
{
	int		fd;
	char	*line;
	char	*path;

	if ((path = sh_getenv(lst_env, "HOME")))
		path = tl_str3join(path, "/", HISTORY);
	fd = open(path, O_RDONLY, S_IRUSR | S_IWUSR);
	ft_strdel(&path);
	if (fd == -1)
		return (GOOD);
	line = NULL;
	while (tl_get_next_line(fd, &line))
		save_command_line(lst_history, line);
	if (close(fd) == -1)
		return (ERROR);
	return (GOOD);
}
