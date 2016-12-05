/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:13:42 by yfuks             #+#    #+#             */
/*   Updated: 2016/12/05 17:46:01 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>

int		exec_is_directory(char *filepath)
{
	struct	stat	path_stat;

	stat(filepath, &path_stat);
	return ((path_stat.st_mode & S_IFMT) == S_IFDIR);
}
