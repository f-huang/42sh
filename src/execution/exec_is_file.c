/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:58:46 by yfuks             #+#    #+#             */
/*   Updated: 2016/11/11 17:58:58 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <unistd.h>
#include <sys/stat.h>

int		exec_is_file(char *filepath)
{
	struct stat path_stat;

	if (access(filepath, F_OK) == -1)
		return (0);
    stat(filepath, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
