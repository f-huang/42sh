/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_through_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:33:33 by fhuang            #+#    #+#             */
/*   Updated: 2017/01/23 18:37:24 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_42sh.h"
#include "libft.h"
#include "input.h"

int	search_through_dir(char *dir_name, char *command)
{
	DIR			*dir;
	t_dirent	*sd;
	int			len;
	char		*tmp;

	if ((dir = opendir(*dir_name == '\0' ? "." : dir_name)) == NULL)
		return (1);
	tmp = ft_strtrim(command);
	len = ft_strlen(tmp);
	while ((sd = readdir(dir)))
	{
		if (ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, ".."))
			continue;
		if (ft_strnequ(sd->d_name, tmp, len))
			ft_lstadd(get_list_completion(), ft_lstnew(sd->d_name, ft_strlen(sd->d_name) + 1));
	}
	ft_strdel(&tmp);
	return (closedir(dir) == -1 ? 1 : 0);
}
